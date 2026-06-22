//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/transaction/truncate_info.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/constants.hpp"

namespace duckdb {
class RowGroupCollection;
class DuckTableEntry;

//! Undo entry for an O(1) TRUNCATE: records the affected row group collection and the
//! truncate generation that this transaction bumped, so commit/rollback can stamp or undo it.
struct TruncateInfo {
	//! The row group collection whose generation was bumped
	RowGroupCollection *collection;
	//! The table whose storage was truncated (used to identify the table when writing to the WAL)
	DuckTableEntry *table;
	//! The generation produced by this truncate
	idx_t generation;
};

} // namespace duckdb
