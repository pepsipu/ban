#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

struct Node {
    char *data;
    struct Node *next;
};
int listLen(struct Node *node) {
    int i = 0;
    while (node->next != NULL) {
        ++i;
        node = node->next;
    }
    return i;
}
struct Node *initList() {
        struct Node *node = malloc(sizeof(struct Node));
        node->data = NULL;
        node->next = NULL;
        return node;
}
struct Node *listIter(struct Node *node, int index) {
    if (node->next == NULL) {
        void *nullptr = NULL;
        return nullptr;
    }
    node = node->next;
    for(int i = 0; i < index; i++) {
        if (node->next == NULL) {
            printf("Index out of bounds");
            exit(0);
        }
        node = node->next;
    }
    return node;
}
char *getIndex(struct Node *node, int index) {
    struct Node *data = listIter(node, index);
    if (data == NULL) return NULL;
    return data->data;
}

void setIndex(struct Node *node, int index, char *newVal) {
    listIter(node, index)->data = newVal;
}

void appendList(struct Node *node, char* data) {
    while (node->next != NULL) {
        node = node->next;
    }
    struct Node *newnode = malloc(sizeof(struct Node));
    newnode->data = data;
    node->next = newnode;
    newnode->next = NULL;
}

void delIndex(struct Node *node, int index) {
    listIter(node, index);
    if (index == 0) {
        if (node->next == NULL) {
            free(node);
        } else {
            struct Node *newtarg;
            setIndex(node, 0, node->next->data);
            if (node->next->next != NULL) {
                newtarg = node->next->next;
            } else {
                newtarg = NULL;
            }
            free(node->next);
            node->next = newtarg;
        }
    } else {
        node = listIter(node, index - 1);
        struct Node *newtarg = node->next->next;
        free(node->next);
        node->next = newtarg;
    }
}


char *pop(struct Node *node) {
    int stacksize = listLen(node);
    char *data = getIndex(node, stacksize - 1);
    delIndex(node, stacksize - 1);
    return data;
}
