//
// Created by pepsipu on 5/26/19.
//

#ifndef SHL_VARIABLE_STORAGE_H
#define SHL_VARIABLE_STORAGE_H

#endif //SHL_VARIABLE_STORAGE_H
struct Node **createTable();
char *lookup(struct Node *keytable, struct Node *datatable, char *key);
void addKey(struct Node *keytable, struct Node *datatable, char *key, char *data);
int exists(struct Node *keytable, struct Node *datatable, char *key, int length);
void setData(struct Node *keytable, struct Node *datatable, char *key, char *data);