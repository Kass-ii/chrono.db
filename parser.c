
// A simplified struct to hold the parsed INSERT command
typedef struct
{
    char *table_name;
    int id; // For now, assume we only insert an id and a name
    char *name;
} InsertStatement;

int parse_insert(const char *query, InsertStatement *stmt)
{

    int result = sscanf(query, "INSERT INTO %s VALUES (%d, %s);",
                        stmt->table_name, &stmt->id, stmt->name);

    if (result == 3)
    {

        return 0;
    }
    else
    {

        return -1;
    }
}