#ifndef WAL_H
#define WAL_H

// Appends a record of a simple key/value insert to the log.
// Returns 0 on success, -1 on failure.
int wal_append_insert(int key, const char *value);

#endif // WAL_H