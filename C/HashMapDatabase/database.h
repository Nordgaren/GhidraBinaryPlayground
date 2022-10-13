#ifndef HASHMAPDATABASE_DATABASE_H
#define HASHMAPDATABASE_DATABASE_H

#include "hashtable.h"
#include "helpers.h"

typedef struct {
    char *path;
    ht_t *map;
} database_t;

database_t *database_create(char *path) {
    database_t *db = malloc(sizeof(database_t));

    db->path = malloc(strlen(path) + 1);;
    strcpy(db->path, path);

    db->map = ht_create();

    char *contents = open_file(path);

    if (contents != NULL && *contents != 0) {
        char *token = strtok(contents, "\n");
        int offset = split_once(token, '\t');
        ht_set(db->map, token, token + offset);

        while (token = strtok(0, "\n")) {
            int offset = split_once(token, '\t');
            ht_set(db->map, token, token + offset);
        }
    }

    return db;
}

void database_insert(database_t *db, char *key, char *value) {
    ht_set(db->map, key, value);
    string_toupper(key);
    ht_set(db->map, key, value);
}

void database_destroy(database_t *db) {
    free(db->map);
}

void database_save(database_t *db) {
    char *contents = ht_tostring(db->map);
    write_file(db->path, contents);
}

char *database_get(database_t *db, char *key) {
    return ht_get(db->map, key);
}


#endif //HASHMAPDATABASE_DATABASE_H
