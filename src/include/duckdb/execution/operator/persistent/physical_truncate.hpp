//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/persistent/physical_truncate.hpp
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/execution/physical_operator.hpp"

namespace duckdb {
class DuckTableEntry;

//! PhysicalTruncate empties a table via DataTable::Truncate.
class PhysicalTruncate : public PhysicalOperator {
public:
	static constexpr const PhysicalOperatorType TYPE = PhysicalOperatorType::TRUNCATE_OPERATOR;

public:
	PhysicalTruncate(PhysicalPlan &physical_plan, vector<LogicalType> types, DuckTableEntry &table,
	                 idx_t estimated_cardinality);

	DuckTableEntry &table;

public:
	bool IsSource() const override {
		return true;
	}

protected:
	SourceResultType GetDataInternal(ExecutionContext &context, DataChunk &chunk,
	                                 OperatorSourceInput &input) const override;
};

} // namespace duckdb
