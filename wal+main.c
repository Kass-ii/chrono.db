#include <stdio.h>
#include <unistd.h> // Required for fsync
#include "wal.h"

// #define LOG_FILE "database.log"
static int next_txn_id = 1;

int wal_append_insert(int key, const char *value, int transaction_id)
{
    FILE *database = fopen("database.txt", "a");
    if (database == NULL)
    {
        perror("Failed to open file ");
        return -1;
    }

    fprintf(database, "%d;INSERT;%d;%s\n", transaction_id, key, value);

    fflush(database);

    int file_descript = fileno(database);
    fsync(file_descript);

    fclose(database);

    return 0;
}

void recover_from_WAL()
{
    FILE *database = fopen("database.txt", "r");
    if (database == NULL)
    {
        printf("error, file did not open - recovery from WAL fn");
        return;
    }

    printf("---Recovery from WAL flagged...starting---");

    char line_buffer[256];

    while (fgets(line_buffer, sizeof(line_buffer), database))
    {
        int key;
        int txn_id;
        char value[100];

        if (sscanf(line_buffer, "%d;INSERT;%d;%99s", &txn_id, &key, value) == 3) // reading so dont need ot pass in a value
        {
            printf("Recovery: Re-applying insert for key %d, value %s\n", key, value);
        }
    }
    printf("--- Recovery Completed ---\n");
    fclose(database);
}

int wal_begin_transaction(void)
{ // multiple transction at once

    /* set varible to the static so you can increment the
    actual static var for next run, and return current number do you have
    the unique identifier  */

    int current = next_txn_id;

    next_txn_id++;

    return current;
}

int wal_commit_transaction(int txt_id)
{ // ensures the finished step is initiated and logged
    FILE *database = fopen("database.txt", "a");
    if (database == NULL)
    {
        perror("Failed to open file - wal commit function");
        return -1;
    }

    fprintf(database, "%d;COMMIT\n", txt_id);

    fflush(database);

    int file_descript = fileno(database);
    fsync(file_descript);

    fclose(database);

    return 0;
}

int main()
{
    /* recovery */
    recover_from_WAL();

    /* generate begin transactions*/
    printf("---starting transaction ID generation---");
    int txt_id = wal_begin_transaction();
    printf("---Transaction started - unique doe is %d---", txt_id);

    /* insert */
    wal_append_insert(102, txt_id, "Bob");
    wal_append_insert(103, txt_id, "Charlie");

    /* commit */
    wal_commit_transaction(txt_id);

    printf("Transactions were logged");
    printf("Check the 'database.log' file to see the results.\n");

    return 0;
}
