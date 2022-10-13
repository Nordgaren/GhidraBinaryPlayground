#ifndef HASHMAPDATABASE_DATABASE_H
#define HASHMAPDATABASE_DATABASE_H
#include "hashtable.h"

typedef struct {
    char *path;
    ht_t *map;
} database_t;

char *open_file(char *path) {
    FILE *in;
    fopen_s(&in, path, "r");
    if (in == NULL) {
        return "";
    }

    fseek(in, 0, SEEK_END);
    long fsize = ftell(in);
    fseek(in, 0, SEEK_SET);  /* same as rewind(in); */

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, in);
    fclose(in);
    string[fsize] = 0;
    return string;

}

void write_file(char *path, char *contents) {
    FILE *out;
    fopen_s(&out, path, "w");
    if (out == NULL) {
        return;
    }
    fputs(contents, out);
    fclose(out);
}

database_t *database_create(char *path) {
    database_t *db = malloc(sizeof(database_t));

    db->path = malloc(strlen(path) + 1);;
    strcpy(db->path, path);

    db->map = ht_create();

    char *contents = open_file(path);


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

    char *contents = "";
    write_file(db->path, contents);
}

char *database_get(database_t *db, char *key) {
    return ht_get(db->map, key);
}


#endif //HASHMAPDATABASE_DATABASE_H
