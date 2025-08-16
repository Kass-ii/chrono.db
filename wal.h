#ifndef WAL_H
#define WAL_H

// Starts a new transaction and returns its ID.
int wal_begin_transaction(void);

// Logs an insert operation as part of a transaction.
int wal_append_insert(int txn_id, int key, const char *value);

// Commits a transaction, making it permanent.
int wal_commit_transaction(int txn_id);

// The recovery function (no changes to its declaration).
void recover_from_wal();

#endif // WAL_H