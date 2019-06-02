//
// Created by pepsipu on 5/26/19.
//

#include "variable_storage.h"
#include "linked_list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node {
    char *data;
    struct Node *next;
};
char *lookup(struct Node *keytable, struct Node *datatable, char *key) {
    int i = 0;
    for (i = 0; i < listLen(keytable); ++i) {
        if (!strcmp(key, getIndex(keytable, i))) {
            return getIndex(datatable, i);
        }
    }
    printf("Key doesn't exist");
    exit(0);
}

void addKey(struct Node *keytable, struct Node *datatable, char *key, char *data) {
    appendList(keytable, key);
    appendList(datatable, data);
}

int exists(struct Node *keytable, struct Node *datatable, char *key, int length) {
    int i = 0;
    for (i = 0; i < length; ++i) {
        if (!strcmp(key, getIndex(keytable, i))) {
            return 1;
        }
    }
    return 0;
}

void setData(struct Node *keytable, struct Node *datatable, char *key, char *data) {
    if (!exists(keytable, datatable, key, listLen(keytable) + 1)) {
        printf("%s does not exist.", key);
        exit(0);
    }
    int i = 0;
    for (i = 0; i < listLen(keytable); ++i) {
        if (!strcmp(key, getIndex(keytable, i))) {
            break;
        }
    }
    setIndex(datatable, i, data);
}