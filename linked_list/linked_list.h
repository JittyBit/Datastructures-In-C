#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct tagList {
  char* data;
  struct tagList* next;
} List;

List* NewList(char* data); // done
int ListAppend(List* list, char* data); // done
char* ListIndex(List* list, int index); // done
int ListRemove(List* list, int index); // done
int ListInsert(List* list, int index, char* data); // done
void ListConcat(List* first, List* second); // done
int ListLength(List* list); // done
int ListPush(List* list, char* data); // done
char* ListPop(List* list); // done
void ListFree(List* list); // done

List* ListReverse(List* list); // done

//TODO: implement Bubble and/or Merge Sort

#endif
