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

    fprintf(database, "INSERT;%d;%s\n", key, value);

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
        return -1;
    }

    printf("---Recovery from WAL flagged...starting---");

    char line_buffer[256];

    while (fgets(line_buffer, sizeof(line_buffer), database))
    {
        int key;
        char value[100];

        if (sscanf(line_buffer, "INSERT;%d;%99s", &key, value) == 2)
        {
            printf("Recovery: Re-applying insert for key %d, value %s\n", key, value);
        }
    }
    printf("--- Recovery Completed ---\n");
    fclose(database);
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

    void recover_from_WAL();

    printf("\nLogging a new operation...\n");
    wal_append_insert(104, "David");
    printf("New operation logged. Program will now exit.\n");

    return 0;
}
