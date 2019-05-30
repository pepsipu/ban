#ifndef SHL_LINKED_LIST_H
#define SHL_LINKED_LIST_H

#endif //SHL_LINKED_LIST_H


struct Node;
extern struct Node *initList();
extern char *getIndex(struct Node *node, int index);
extern void appendList(struct Node *node, char* data);
extern void delIndex(struct Node *node, int index);
extern void setIndex(struct Node *node, int index, char *newVal);
extern int listLen(struct Node *node);
extern char *pop(struct Node *node);