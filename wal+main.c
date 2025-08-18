#include <stdio.h>
#include <stdlib.h> // Required for atoi
#include <string.h> // Required for strtok, strncmp, etc.
#include <unistd.h> // Required for fsync

// --- Constants and Global State ---

// Define a constant for the log file name for easier changes.
#define LOG_FILE_NAME "database.txt"
#define MAX_COMMITTED_TXNS 100
#define MAX_LINE_BUFFER 2048

// A static variable to ensure transaction IDs are always unique.
static int next_txn_id = 1;

// --- Core Write-Ahead Log (WAL) Functions ---

int wal_append_insert(int key, const char *value, int transaction_id)
{
    FILE *database = fopen(LOG_FILE_NAME, "a");
    if (database == NULL)
    {
        perror("Failed to open file in wal_append_insert");
        return -1;
    }

    fprintf(database, "%d;INSERT;%d;%s\n", transaction_id, key, value);

    // Ensure the data is written from memory buffers to the OS.
    fflush(database);

    int file_descriptor = fileno(database);
    fsync(file_descriptor);

    fclose(database);
    return 0;
}

int wal_commit_transaction(int txn_id)
{
    FILE *database = fopen(LOG_FILE_NAME, "a");
    if (database == NULL)
    {
        perror("Failed to open file in wal_commit_transaction");
        return -1;
    }

    fprintf(database, "%d;COMMIT\n", txn_id);

    fflush(database);
    int file_descriptor = fileno(database);
    fsync(file_descriptor);

    fclose(database);
    return 0;
}

int wal_begin_transaction(void)
{
    // Atomically increment and return the next transaction ID.
    return next_txn_id++;
}

void recover_from_WAL()
{
    FILE *database = fopen(LOG_FILE_NAME, "r");
    if (database == NULL)
    {
        // If the log file doesn't exist, it's not an error. It's a fresh start.
        printf("--- No existing WAL file found. Starting fresh. ---\n");
        return;
    }

    printf("--- Recovery from WAL flagged... starting ---\n");

    int commit_count = 0;
    int committed_txns[MAX_COMMITTED_TXNS];
    char line_buffer[MAX_LINE_BUFFER];

    // First pass: Find all transaction IDs that were successfully committed.
    while (fgets(line_buffer, sizeof(line_buffer), database))
    {
        int txn_id;
        if (sscanf(line_buffer, "%d;COMMIT", &txn_id) == 1)
        {
            if (commit_count < MAX_COMMITTED_TXNS)
            {
                committed_txns[commit_count++] = txn_id;
            }
        }
    }

    // Reset the file pointer to the beginning for the second pass.
    rewind(database);

    // Second pass: Re-apply operations for committed transactions.
    while (fgets(line_buffer, sizeof(line_buffer), database))
    {
        int key, txn_id;
        char value[100];

        if (sscanf(line_buffer, "%d;INSERT;%d;%99s", &txn_id, &key, value) == 3)
        {
            int was_committed = 0;
            for (int i = 0; i < commit_count; i++)
            {
                if (committed_txns[i] == txn_id)
                {
                    was_committed = 1;
                    break;
                }
            }

            if (was_committed)
            {
                // In a real database, you would apply this to your in-memory data structure (like a B+ Tree).
                printf("Recovery: Re-applying insert for key %d, value %s\n", key, value);
            }
        }
    }

    printf("--- Recovery Complete ---\n");
    fclose(database);
}

void execute_sql(const char *sql)
{
}

int main(void)
{
    // Always run recovery first to restore state from the last run.
    recover_from_WAL();

    char sql_buffer[MAX_LINE_BUFFER];
    long query_count = 0;

    printf("--- ChronoDB Engine Ready. Awaiting SQL from stdin. ---\n");

    while (fgets(sql_buffer, sizeof(sql_buffer), stdin) != NULL)
    {
        // Remove the trailing newline character that fgets reads.
        sql_buffer[strcspn(sql_buffer, "\n")] = 0;

        // If the line isn't empty, execute it.
        if (strlen(sql_buffer) > 0)
        {
            execute_sql(sql_buffer);
            query_count++;
        }
    }

    //  GitHub Action will parse.
    printf("--- Benchmark Complete ---\n");
    // In a real test, you would time this and calculate QPS accurately.
    // For now, we print a placeholder value based on the query count.
    printf("Total Queries Processed: %ld\n", query_count);
    printf("teest\n"); // Placeholder QPS

    return 0;
}
