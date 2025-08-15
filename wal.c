#include <stdio.h>
#include <unistd.h> // Required for fsync
#include "wal.h"

#define LOG_FILE "database.log"

int wal_append_insert(int key, const char *value)
{
    FILE *database = fopen("database.txt", "a");
    if (database == NULL)
    {
        perror("Failed to open file ");
        return -1;
    }

    fprintf(database, "INSERT;%d;%s;TESTLINE\n", key, value);

    fflush(database);

    int file_descript = fileno(database);
    fsync(file_descript);

    fclose(database);

    return 0;
}

int main()
{
    printf("Logging an operation...\n");
    int result = wal_append_insert(101, "Alice");
    if (result == 0)
    {
        printf("Log entry written successfully.\n");
    }
    else
    {
        printf("Failed to write log entry.\n");
    }

    wal_append_insert(102, "Bob");
    wal_append_insert(103, "Charlie");

    printf("Check the 'database.log' file to see the results.\n");

    return 0;
}
