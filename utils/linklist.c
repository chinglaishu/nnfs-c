#include <stdio.h>
#include <stdlib.h>
#include "./linklist.h"

typedef struct use0 {
  int name;
} Use0;

typedef struct use1 {
  double id;
} Use1;

void linkList_print(LinkList *list) {
  Node *ptr = list->startNode;
  printf("start\n");
  while(ptr != NULL) {
    printf("data: %p\n", ptr->data);
    ptr = ptr->next;
  }
  printf("end\n");
};

/*
void linkList_print(LinkList *list) {
  Node *ptr = list->startNode;

  while(ptr != NULL) {
    printf("data: %p\n", ptr->data);
    printf("\n Element is: %s \n", ptr->type);
    int cmp = strcmp("use0", ptr->type);
    printf("cmp: %d\n", cmp);
    if (cmp == 0) {
      Use0 *data = (Use0 *) ptr->data;
      printf("use0 name: %d\n", data->name);
    } else {
      Use1 *data = (Use1 *) ptr->data;
      printf("use1 id: %f\n", data->id);
    }
    ptr = ptr->next;
  }
  printf("end\n");
};
*/

void linkList_push(LinkList *list, int *data, char *type) {
  Node *link = (Node *) malloc(sizeof(Node));
  link->data = data;
  link->type = type;
  link->next = NULL;
  Node *ptr = list->startNode;
  if (ptr == NULL) {
    list->startNode = link;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = link;
};

void linkList_unshift(LinkList *list, int *data, char *type) {
  Node *link = (Node *) malloc(sizeof(Node));
  link->data = data;
  link->type = type;
  if (list->startNode == NULL) {
    link->next = NULL;
    list->startNode = link;
    return;
  }
  link->next = list->startNode;
  list->startNode = link;
};

void linkList_insert(LinkList *list, int insertIndex, int *data, char *type) {
  if (insertIndex == 0 || list->startNode == NULL) {
    linkList_unshift(list, data, type);
    return;
  }
  Node *nextItem = (Node *) malloc(sizeof(Node));
  nextItem->data = data;
  nextItem->type = type;
  Node *ptr = list->startNode;
  int recordIndex = 0;
  while (ptr != NULL) {
    if (recordIndex + 1 == insertIndex) {
      nextItem->next = ptr->next;
      ptr->next = nextItem;
      return;
    }
    recordIndex += 1;
    ptr = ptr->next;
  }
  printf("error linkList_insert");
};

void linkList_deleteItem(LinkList *list, int deleteIndex) {
  Node *ptr = list->startNode;
  if (deleteIndex == 0 && ptr != NULL) {
    list->startNode = ptr->next;
    return;
  }
  int recordIndex = 0;
  while (ptr != NULL) {
    if (recordIndex + 1 == deleteIndex) {
      Node *nextItem = ptr->next;
      ptr->next = nextItem->next;
      return;
    }
    recordIndex += 1;
    ptr = ptr->next;
  }
  printf("error linkList_deleteItem");
}

void linkListReverse(LinkList *newList, LinkList *list) {
  Node *ptr = list->startNode;
  while (ptr != NULL) {
    linkList_unshift(newList, ptr->data, ptr->type);
    ptr = ptr->next;
  }
}

Node *linkList_getLastItem(LinkList *list) {
  Node *ptr = list->startNode;
  if (ptr == NULL) {return ptr; }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  return ptr;
}

/*
int main() {
  LinkList list = {};
  Use0 use0;
  use0.name = 10;
  Use1 use1;
  use1.id = 11.4;
  char arr3[3]; 
  linkList_print(&list);
  linkList_push(&list, &use0, "use0");
  linkList_unshift(&list, &use1, "use1");
  linkList_print(&list);
  LinkList list2 = {};
  linkListReverse(&list2, &list);
  linkList_print(&list2);
  return 0;
}
*/
