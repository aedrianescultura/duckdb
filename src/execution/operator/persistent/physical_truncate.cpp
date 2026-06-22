#include "duckdb/execution/operator/persistent/physical_truncate.hpp"
#include "duckdb/catalog/catalog_entry/duck_table_entry.hpp"
#include "duckdb/storage/data_table.hpp"

namespace duckdb {

PhysicalTruncate::PhysicalTruncate(PhysicalPlan &physical_plan, vector<LogicalType> types, DuckTableEntry &table,
                                   idx_t estimated_cardinality)
    : PhysicalOperator(physical_plan, PhysicalOperatorType::TRUNCATE_OPERATOR, std::move(types), estimated_cardinality),
      table(table) {
}

SourceResultType PhysicalTruncate::GetDataInternal(ExecutionContext &context, DataChunk &chunk,
                                                   OperatorSourceInput &input) const {
	table.GetStorage().Truncate(context.client, table);
	return SourceResultType::FINISHED;
}

} // namespace duckdb
