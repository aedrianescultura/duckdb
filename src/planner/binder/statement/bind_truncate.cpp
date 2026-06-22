#include "duckdb/catalog/catalog.hpp"
#include "duckdb/catalog/catalog_entry/table_catalog_entry.hpp"
#include "duckdb/parser/constraints/foreign_key_constraint.hpp"
#include "duckdb/parser/statement/truncate_statement.hpp"
#include "duckdb/planner/binder.hpp"
#include "duckdb/planner/operator/logical_truncate.hpp"

namespace duckdb {

static bool TableIsReferencedByForeignKey(TableCatalogEntry &table) {
	// A table is "referenced" if it holds a FOREIGN KEY constraint of type
	// FK_TYPE_PRIMARY_KEY_TABLE (another table's FK points at this table) or
	// FK_TYPE_SELF_REFERENCE_TABLE (the table references itself).
	// DuckDB records the referenced side as such a constraint on the referenced table.
	for (const auto &constraint : table.GetConstraints()) {
		if (constraint->type != ConstraintType::FOREIGN_KEY) {
			continue;
		}
		auto &fk = constraint->Cast<ForeignKeyConstraint>();
		if (fk.info.IsDeleteConstraint()) {
			return true;
		}
	}
	return false;
}

BoundStatement Binder::Bind(TruncateStatement &stmt) {
	auto &table = Catalog::GetEntry<TableCatalogEntry>(context, stmt.table->catalog_name, stmt.table->schema_name,
	                                                   stmt.table->table_name);

	if (TableIsReferencedByForeignKey(table)) {
		throw BinderException("Cannot truncate table \"%s\" because it is referenced by a foreign key constraint",
		                      table.name);
	}

	if (!table.temporary) {
		// Truncating a persistent table modifies the database.
		auto &properties = GetStatementProperties();
		properties.RegisterDBModify(table.catalog, context, DatabaseModificationType::DELETE_DATA);
	}

	auto truncate = make_uniq<LogicalTruncate>(table, GenerateTableIndex());

	BoundStatement result;
	result.plan = std::move(truncate);
	result.types = {LogicalType::BOOLEAN};
	result.names = {"Success"};
	auto &properties = GetStatementProperties();
	properties.return_type = StatementReturnType::NOTHING;
	properties.output_type = QueryResultOutputType::FORCE_MATERIALIZED;
	return result;
}

} // namespace duckdb
