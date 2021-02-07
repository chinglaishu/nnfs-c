#ifndef __linklist_H
#define __linklist_H

typedef struct node {
  int *data;
  char *type;
  struct node *next;
} Node;

typedef struct linkList {
  Node *startNode;
} LinkList;

void linkList_print(LinkList *list);

void linkList_push(LinkList *list, int *data, char *type);

void linkList_unshift(LinkList *list, int *data, char *type);

void linkList_insert(LinkList *list, int insertIndex, int *data, char *type);

void linkList_deleteItem(LinkList *list, int deleteIndex);

void linkListReverse(LinkList *newList, LinkList *list);

Node *linkList_getLastItem(LinkList *list);

#endif
