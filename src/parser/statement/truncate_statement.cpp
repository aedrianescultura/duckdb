#include "duckdb/parser/statement/truncate_statement.hpp"

namespace duckdb {

TruncateStatement::TruncateStatement() : SQLStatement(StatementType::TRUNCATE_STATEMENT) {
}

TruncateStatement::TruncateStatement(const TruncateStatement &other)
    : SQLStatement(other), table(unique_ptr_cast<TableRef, BaseTableRef>(other.table->Copy())) {
}

string TruncateStatement::ToString() const {
	D_ASSERT(table);
	string result = "TRUNCATE TABLE ";
	result += table->ToString();
	return result;
}

unique_ptr<SQLStatement> TruncateStatement::Copy() const {
	return unique_ptr<TruncateStatement>(new TruncateStatement(*this));
}

} // namespace duckdb
