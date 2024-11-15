#include "vector.h"

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>


#ifndef VECTOR_STEP 
#define VECTOR_STEP 10
#endif 

/*
 typedef struct {
  int len;
  int cap;
  void** buffer;
 }
*/


Vector* VectorInit(int cap){
  Vector* vec = (Vector*) malloc(sizeof(Vector));
  if (!vec)
    return NULL;
  if (cap < 0)
    return NULL;
  vec->len = 0;
  vec->cap = cap;
  void** buffer = (void**) malloc(sizeof(void*)*cap);
  if (!buffer)
    return NULL;
  vec->buffer = buffer;
  return vec;
}

void VectorFree(Vector* vec) {
  if (!vec)
    return;
  for (int i = 0; i < vec->len; i++) {
    free(vec->buffer[i]);
  }
  free(vec);
}

static int __resize(Vector* vec, int new_cap) {
  if (!vec)
    return 1;
  void* old_buf = vec->buffer;
  vec->buffer = (void**) realloc(vec->buffer, new_cap*sizeof(void*));
  if (!vec->buffer)
    vec->buffer = old_buf;
    return -1;
  vec->cap = new_cap;
  return 0;
}

int VectorAppend(Vector* vec, void* elem) {
  if (!vec)
    return 1;
  if (vec->len+1 > vec->cap) {
    int err = __resize(vec, vec->cap+VECTOR_STEP);
    if (err == -1) {
      return -1;
    }
  }
  vec->buffer[vec->len] = elem;
  vec->len++;
  return 0;
}

// returns # of elements appended
int VectorAppendMany(Vector* vec, int count,...) {
  if (!vec)
    return 1; 
  
  int n = 0;
  va_list args;
  va_start(args, count);
  
  for (int i = 0; i < count; i++) {
    if (VectorAppend(vec, va_arg(args, void*)) != 0)
      break;
    n++;
  }
  return n;
}

int VectorConcat(Vector* first, Vector* second) {
  if (!first || !second)
    return 1;
  int err = __resize(first, first->cap+second->len);
  if (err != 0)
    return err;
  for (int i = 0; i < second->len; i++) {
    if (VectorAppend(first, second->buffer[i]))
      return -1;
  }
  return 0;
}

int VectorRemove(Vector* vec, int index) {
  if (!vec)
    return 1;
  if (index > vec->cap)
    return 2;
  index = (index<0)? vec->len-index : index;
  memmove(vec->buffer+index, vec->buffer+index+1, vec->len - index);
  vec->len--;
  return 0;
}

int VectorInsert(Vector* vec, int index, void* elem) {
  if (!vec)
    return 1;
  if (index > vec->cap)
    return 2;
  if (vec->len+1 > vec->cap) {
    int err = __resize(vec, vec->cap+VECTOR_STEP);
    if (err != 0)
      return err;
    memmove(vec->buffer+index+1, vec->buffer+index, vec->len-index+1); // guh
  }
  vec->buffer[index] = elem;
  vec->len++;
  return 0;
}

void* VectorPop(Vector* vec) { 
  if (!vec)
    return NULL;
  return vec->buffer[vec->len--];
}

void* VectorIndex(Vector* vec, int index) {
  if (!vec)
    return NULL;
  return vec->buffer[index];
}

// returns index of element in vector
// else returns -1
int VectorSearch(Vector* vec, void* elem) {
  if (!vec)
    return -1;
  int i = 0;
  int j = vec->len;
  int guess;
  while (1) {
    guess = (i+j)/2;
    if (vec->buffer[guess] == elem) {
      return guess;
    } else if (vec->buffer[guess] < elem) {
      i = guess;
    } else if (vec->buffer[guess] > elem) {
      j = guess;
    }
  }
  // THE PROGRAM SHOULD NOT GET HERE
  return 69;
}

// could modify code to use bitwise ops instead
// but compiler could just be optimizing this
static void inline __swap(void** a, void** b) {
  void* temp = *a;
  *a = *b;
  *b = temp;
}

static int __part(void** list, int len) {
  int p = len-1; 
  int i = 0;
  int j = p-1;
  while (1) {
    for (; list[i] <= list[p] && i < p; i++);
    for (; list[j] >= list[p] && j > 0; j--);
    if (i >= j) break;
    __swap(list+i, list+j);
  }
  __swap(list+i,list+p);
  return i;
}

static void __qsort(void** list, int len) {
  if (len < 2) return;
  int pivot = __part(list, len);
  
  __qsort(list, pivot);
  __qsort(list+pivot+1, len-pivot-1);
}

void VectorSort(Vector* vec) {
  if (!vec)
    return;
  __qsort(vec->buffer, vec->len);
}

// 1 2 3 4 5
void VectorReverse(Vector* vec) {
  for (int i = 0, j = vec->len; i < j; ++i,--j) {
    __swap(vec->buffer+i, vec->buffer+vec->len-j-1);
  } 
}
