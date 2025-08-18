#include <stdbool.h>

typedef enum
{
    LOCK_SHARED,
    LOCK_EXCLUSIVE
} LockMode;

typedef enum
{
    STATUS_GRANTED,
    STATUS_WAITING
} LockStatus;

typedef struct LockRequest
{
    int transaction_id;
    LockMode mode;
    LockStatus status;
    struct LockRequest *next;
} LockRequest;

// A struct to hold the list of locks for one resource
typedef struct LockListEntry
{
    int resource_id;   // This is the key for the hash map
    LockRequest *head; // Pointer to the first lock in the list
    UT_hash_handle hh; // This makes the struct hashable with uthash
} LockListEntry;