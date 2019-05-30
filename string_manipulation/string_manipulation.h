#include <stdbool.h>

#ifndef SHL_STRING_MANIPULATION_H
#define SHL_STRING_MANIPULATION_H

#endif

bool startsWith(const char *pre, const char *str);
struct Node *split(char *string, const char *delimiter);
void parse(char *statement, struct Node *keyTable, struct Node *dataTable,  struct Node *funcNames, struct Node *funcEIP, struct Node *virtStack, int *eip, int * oldEip, bool *inFunc);