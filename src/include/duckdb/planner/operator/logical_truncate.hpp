//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/operator/logical_truncate.hpp
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/planner/logical_operator.hpp"

namespace duckdb {
class TableCatalogEntry;

class LogicalTruncate : public LogicalOperator {
public:
	static constexpr const LogicalOperatorType TYPE = LogicalOperatorType::LOGICAL_TRUNCATE;

public:
	LogicalTruncate(TableCatalogEntry &table, TableIndex table_index);

	TableCatalogEntry &table;
	TableIndex table_index;

public:
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<LogicalOperator> Deserialize(Deserializer &deserializer);
	string GetName() const override;

protected:
	vector<ColumnBinding> GetColumnBindings() override;
	void ResolveTypes() override;
};
} // namespace duckdb
