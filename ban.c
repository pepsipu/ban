#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string_manipulation/string_manipulation.h"
#include "memory/linked_list.h"
#include "memory/variable_storage.h"

char *fileContents(FILE *filename) {
    fseek(filename, 0, SEEK_END);
    long filesize = ftell(filename);
    fseek(filename, 0, SEEK_SET);
    char* contents = (char *) calloc(filesize, sizeof(char));
    fread(contents, sizeof(char), filesize, filename);
    return contents;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>.\n", argv[0]);
        exit(0);
    }
    struct Node *varKeys = initList();
    struct Node *varData = initList();
    struct Node *funcNames = initList();
    struct Node *funcEIP = initList();
    struct Node *virtStack = initList();
    FILE *shlfile = fopen(argv[1], "r");
    if (!shlfile) {
        printf("%s is not a valid file.\n", argv[1]);
        exit(0);
    }
    char *contents = fileContents(shlfile);
    fclose(shlfile);
    struct Node *statements = split(contents, ";\n");
    int len = listLen(statements);
    int eip = 0;
    bool inFunc = false;
    int oldEip = 0;
    while (eip < len) {
        parse(getIndex(statements, eip), varKeys, varData, funcNames, funcEIP, virtStack, &eip, &oldEip, &inFunc);
        ++eip;
        if (!inFunc) {
            oldEip = eip;
        }
    }
}
