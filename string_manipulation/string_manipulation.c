#include "string_manipulation.h"
#include "../memory/linked_list.h"
#include "../memory/variable_storage.h"
#include "../logic/virtual_gates.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char *strSlice(const char * str, size_t start, size_t end)
{
    size_t j = 0;
    char *buffer = malloc(strlen(str) + 1);
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
    return buffer;
}
char *replaceWord(const char *s, const char *oldW, const char *newW) {
    char *result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr(&s[i], oldW) == &s[i])
        {
            cnt++;
            i += oldWlen - 1;
        }
    }
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);
    i = 0;
    while (*s) {
        if (strstr(s, oldW) == s)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
    result[i] = '\0';
    return result;
}

void error(char *msg, int eip) {
    printf("ERROR: Line %d\n", eip + 1);
    printf("%s", msg);
    exit(0);
}

struct Node *split(char *string, const char *delimiter) {
    struct Node *list = initList();
    char *writeEnabledString = malloc(strlen(string) + 1);
    strcpy(writeEnabledString, string);
    char *token = strtok(writeEnabledString, delimiter);
    while (token != NULL) {
        appendList(list, token);
        token = strtok(NULL, delimiter);
    }
    return list;
}


char *eval(char *statement, int rightP) {
    int rightLocation = 0;
    int leftLocation = 0;
    for (int i = 0; i < strlen(statement); ++i) {
        if (statement[i] == '(') --rightP;
        if (rightP == 0) {
            rightLocation = i;
            break;
        }
    }
    for (int i = rightLocation; i < strlen(statement); ++i) {
        if (statement[i] == ')') {
            leftLocation = i;
            break;
        }
    }
    return strSlice(statement, rightLocation, leftLocation);
}
char *parenthesisParse(char *string, struct Node *keyTable, struct Node *dataTable, struct Node *virtStack, int *eip);

char *boolOrVar(char *value, struct Node *keyTable, struct Node *dataTable, struct Node *virtStack, int *eip) {
    if (value[0] == '(') parenthesisParse(value, keyTable, dataTable, virtStack, eip);
    if (!strcmp(value, "[pop]")) return pop(virtStack);
    if (!strcmp(value, "0") || !strcmp(value, "1")) return value;
    if (!exists(keyTable, dataTable, value, listLen(keyTable) + 1)) error("Variable does not exist.", *eip);
    return lookup(keyTable, dataTable, value);
}

char *logicParse(char *string, struct Node *keyTable, struct Node *dataTable, struct Node *virtStack, int *eip) {
    struct Node *logicStatement = split(string, " ");
    char *opcode = string[0];
    if (opcode == '+') {
        return or(boolOrVar(getIndex(logicStatement, 1), keyTable, dataTable, virtStack, eip), boolOrVar(getIndex(logicStatement, 2), keyTable, dataTable, virtStack, eip));
    } else if (opcode == '*') {
        return and(boolOrVar(getIndex(logicStatement, 1), keyTable, dataTable, virtStack, eip), boolOrVar(getIndex(logicStatement, 2), keyTable, dataTable, virtStack, eip));
    } else if (opcode =='!') {
        return not(boolOrVar(getIndex(logicStatement, 1), keyTable, dataTable, virtStack, eip));
    }
}

char *parenthesisParse(char *string, struct Node *keyTable, struct Node *dataTable, struct Node *virtStack, int *eip) {
    int rightP = 0;
    int leftP = 0;
    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] == '(') ++rightP;
        if (string[i] == ')') ++leftP;
    }
    if (rightP != leftP) {
        error("Unbalanced parenthesis.", *eip);
    }
    char *looperWord = string;
    int rightPCpy = rightP;
     for (int i = 0; i < rightPCpy; i++){
        rightP = 0;
        for (int f = 0; f < strlen(looperWord); ++f) {
            if (looperWord[f] == '(') ++rightP;
        }
        char *currentParenthesis = eval(looperWord, rightP);
        char *parsed = logicParse(strSlice(currentParenthesis, 1, strlen(currentParenthesis) - 2), keyTable, dataTable, virtStack, eip);
        looperWord = replaceWord(looperWord, currentParenthesis, parsed);
    }
    return logicParse(looperWord, keyTable, dataTable, virtStack, eip);
}
void parse(char *statement, struct Node *keyTable, struct Node *dataTable,  struct Node *funcNames, struct Node *funcEIP, struct Node *virtStack, int *eip, int *oldEip, bool *inFunc) {
    if (!*inFunc && statement[0] == '\t' || !*inFunc && !strncmp(statement, "    ", 4)) return;
    if (statement[0] == '\t') {
        statement = replaceWord(statement, "\t", "");
    }
    struct Node *lineSplit = split(statement, " ");
    char *opcode = getIndex(lineSplit, 0);
    if (!strcmp(opcode, "define")) {
        if (exists(keyTable, dataTable, getIndex(lineSplit, 1), listLen(keyTable))) {
            return;
        }
        addKey(keyTable, dataTable, getIndex(lineSplit, 1), NULL);
    } else if (!strcmp(opcode, "set")) {
        if (strcmp(getIndex(lineSplit, 2), "=")) {
            error("Unknown data assignment", *eip);
        }
        setData(keyTable, dataTable, getIndex(lineSplit, 1),
                    boolOrVar(getIndex(lineSplit, 3), keyTable, dataTable, virtStack, eip));
    }
    else if (!strcmp(opcode, "push")) {
        appendList(virtStack, boolOrVar(getIndex(lineSplit, 1), keyTable, dataTable, virtStack, eip));
    }
    else if (!strcmp(opcode, "pop")) {
        if (!exists(keyTable, dataTable, getIndex(lineSplit, 1), listLen(lineSplit) + 1)) {
            error("Variable does not exist.", *eip);
        }
        setData(keyTable, dataTable, getIndex(lineSplit, 1), pop(virtStack));
    }
    else if (!strcmp(opcode, "debug")) {
        printf("$VARIABLES: {\n");
        for (int i = 0; i < listLen(keyTable); ++i) {
            printf("\t'%s': '%s',\n", getIndex(keyTable, i), getIndex(dataTable, i));
        }
        printf("}\n");
        printf("$FUNCTIONS: {\n");
        for (int i = 0; i < listLen(funcNames); ++i) {
            printf("\t'%s': '%s',\n", getIndex(funcNames, i), getIndex(funcEIP, i));
        }
        printf("}\n");
        printf("$STACK: [\n");
        for (int i = listLen(virtStack); i > 0; --i) {
            char *stackVal = getIndex(virtStack, i - 1);
            if (stackVal != NULL) {
                printf("\t'%s',\n", stackVal);
            }
        }
        printf("]\n");
    }
    else if (!strcmp(opcode, "+") || !strcmp(opcode, "*") || !strcmp(opcode, "!")) {
        appendList(virtStack, parenthesisParse(statement, keyTable, dataTable, virtStack, eip));
    }
    else if (!strcmp(opcode, "func")) {
        appendList(funcNames, getIndex(lineSplit, 1));
        int length = snprintf( NULL, 0, "%d", *eip + 1);
        char *intBuffer = malloc(length + 1);
        snprintf(intBuffer, length + 1, "%d", *eip + 1);
        appendList(funcEIP, intBuffer);
    }
    else if (!strcmp(opcode, "call")) {
        if (exists(funcNames, funcEIP, getIndex(lineSplit, 1), listLen(funcNames))) {
            *eip = (lookup(funcNames, funcEIP, getIndex(lineSplit, 1))[0] - '0') - 1;
            *inFunc = true;
        }
    }
    else if (!strcmp(opcode, "return")) {
        *eip = *oldEip;
        *inFunc = false;
    }
}