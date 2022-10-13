#include "database.h"

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("No arguments passed to program.");
        return -1;
    }

    database_t *db = database_create("sample_c.db");
    char *arg = argv[1];
    if (memcmp(arg, "set", 3) == 0) {
        char *key = argv[2];
        char *value = argv[3];

        printf("Added new entry: The key is '%s' and the value is '%s'", key, value);
        database_insert(db, key, value);
        database_save(db);
    } else if (memcmp(arg, "get", 3) == 0) {
        char *key = argv[2];
        char *value = database_get(db, key);
        printf("The value of '%s' is '%s'\n", key, value);
    }

    database_destroy(db);
    return 0;
}

