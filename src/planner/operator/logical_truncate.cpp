#include "duckdb/planner/operator/logical_truncate.hpp"

namespace duckdb {

LogicalTruncate::LogicalTruncate(TableCatalogEntry &table, TableIndex table_index)
    : LogicalOperator(LogicalOperatorType::LOGICAL_TRUNCATE), table(table), table_index(table_index) {
}

void LogicalTruncate::ResolveTypes() {
	// TRUNCATE produces no result rows, but (like other no-result DML) carries a single
	// placeholder column so the result collection has a valid, non-empty type list.
	types.emplace_back(LogicalType::BOOLEAN);
}

vector<ColumnBinding> LogicalTruncate::GetColumnBindings() {
	return {ColumnBinding(table_index, ProjectionIndex(0))};
}

string LogicalTruncate::GetName() const {
	return "TRUNCATE";
}

void LogicalTruncate::Serialize(Serializer &serializer) const {
	throw NotImplementedException("TRUNCATE cannot be serialized as a logical plan");
}

unique_ptr<LogicalOperator> LogicalTruncate::Deserialize(Deserializer &deserializer) {
	throw NotImplementedException("TRUNCATE cannot be deserialized as a logical plan");
}

} // namespace duckdb
