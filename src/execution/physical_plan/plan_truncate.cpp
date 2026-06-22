#include "duckdb/catalog/catalog_entry/duck_table_entry.hpp"
#include "duckdb/execution/operator/persistent/physical_truncate.hpp"
#include "duckdb/execution/physical_plan_generator.hpp"
#include "duckdb/planner/operator/logical_truncate.hpp"

namespace duckdb {

PhysicalOperator &PhysicalPlanGenerator::CreatePlan(LogicalTruncate &op) {
	auto &table = op.table.Cast<DuckTableEntry>();
	return Make<PhysicalTruncate>(op.types, table, op.estimated_cardinality);
}

} // namespace duckdb
