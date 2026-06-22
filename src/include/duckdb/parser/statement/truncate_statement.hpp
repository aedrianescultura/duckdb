//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/truncate_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/sql_statement.hpp"
#include "duckdb/parser/tableref/basetableref.hpp"

namespace duckdb {

class TruncateStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::TRUNCATE_STATEMENT;

public:
	TruncateStatement();

	//! The table to truncate
	unique_ptr<BaseTableRef> table;

protected:
	TruncateStatement(const TruncateStatement &other);

public:
	string ToString() const override;
	unique_ptr<SQLStatement> Copy() const override;
};

} // namespace duckdb
