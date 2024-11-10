#include "linked_list.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define UNIMPLEMENTED(msg) fprintf(stderr, msg)

#define NEG_INDEX_UNIMPL \
  UNIMPLEMENTED("NEGATIVE INDEXING UNIMPLEMENTED"); \
  return 2

/*
 * RETURN CODES:
 * 0  = SUCCESS
 * -1 = MALLOC ERROR
 * 1  = NULL POINTER ERROR
 * 2  = INDEX OUT OF BOUNDS ERROR 
 */

List* NewList(char* data) {
  List* list = (List*) malloc(sizeof(List));
  if (!list)
    return NULL;
  list->next = NULL;
  list->data = strdup(data);
  if (!list->data) {
    free(list);
    return NULL;
  }
  return list;
}

//IMPORTANT: This function sends the pointer passed
//           to it out of scope. Do NOT double free
//           it later! Not meant for usage outside
//           of the file.
static void __freeNode(List* list) {
  free(list->data);
  free(list);
}

//IMPORTANT: this function is similar to __freeNode()
//           in how it sends the freed list out of
//           scope. Do NOT double free after usage.
void ListFree(List* list) {
  List* temp;
  while (list) {
    temp = list;
    list = list->next;
    __freeNode(temp);
  }
}

int ListAppend(List* list, char* data) {
  if (!list)
    return 1;
  List* node = NewList(data);
  if (!node)
    return -1;
  List* curr = list;
  while (curr->next) {
    curr = curr->next;
  }
  curr->next = node;
  return 0;
}

//TODO: implement negative indexing
int ListInsert(List* list, int index, char* data) {
  if (!list)
    return 1;
  if (index < 0) {
    NEG_INDEX_UNIMPL;
  }
  List* node = NewList(data);
  if (!node)
    return -1;
  List* curr = list;
  int i = 0;
  do {
    curr = list->next;
    i++;
  } while (i < index-1 && curr);
  if (!curr) {
    __freeNode(node);
    return 2;
  }
  List* next = curr->next;
  curr->next = node;
  node->next = next;
  return 0;
}

//TODO: implement negative indexing
int ListRemove(List* list, int index) {
  if (!list)
    return 1;
  if (index < 0) {
    NEG_INDEX_UNIMPL;
  }
  List* curr = list;
  int i = 0;
  do {
    curr = list->next;
    i++;
  } while (i < index-1 && curr);
  if (!curr)
    return 2;
  List* next = curr->next->next;
  __freeNode(curr->next);
  curr->next = next;
  return 0;
}

char* ListIndex(List* list, int index) {
  if (!list)
    return NULL;
  if (index < 0) {
    //NEG_INDEX_UNIMPL;
    fprintf(stderr, "NEGATIVE INDEXING UNIMPLEMENTED\n");
    return NULL;
  }
  List* curr = list;
  int i = 0;
  do {
    curr = list->next;
    i++;
  } while (i < index && curr);
  if (!curr)
    return NULL;
  return curr->data;
}

void ListConcat(List* first, List* second) {
  if (!first)
    return;
  List* curr = first;
  while (curr->next) {
    curr = curr->next;
  }
  curr->next = second;
  return;
}

int ListLength(List* list) {
  int length = 0;
  List* curr = list;
  while (curr) {
    length++;
    curr = curr->next;
  }
  return length;
}

int ListPush(List* list, char* data) {
  if (!list)
    return 1;
  List* node = NewList(data);
  if (!node)
    return -1;
  List* curr = list;
  while (curr->next) {
    curr = curr->next;
  }
  curr->next = node;
  return 0;
}

char* ListPop(List* list) {
  if (!list)
    return NULL;
  List* curr = list;
  while (curr->next) {
    curr = curr->next;
  }
  char* data = strdup(curr->data);
  __freeNode(curr);
  return data;
}

List* ListReverse(List* list) {
  List* head = NULL;
  List* prev;
  while (list) {
    prev = list;
    list = list->next;
    prev->next = head;
    head = prev;
  }
  return head;
}

















