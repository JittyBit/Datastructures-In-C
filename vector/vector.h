#ifndef VECTOR_H 
#define VECTOR_H

#include <stddef.h>

// resize step defined by VECTOR_STEP macro(?)
typedef struct {
  int len;
  int cap;
  void** buffer;
} Vector;

Vector* VectorInit(int cap);
void VectorFree(Vector* vec);

int VectorAppend(Vector* vec, void* elem);
int VectorAppendMany(Vector* vec, int count,...);
int VectorConcat(Vector* first, Vector* second);

int VectorRemove(Vector* vec, int index);
int VectorInsert(Vector* vec, int index, void* elem);
void* VectorPop(Vector* vec);
void* VectorIndex(Vector* vec, int index);

// searching/sorting memory locations
// is kinda useless, but idrc rn
int VectorSearch(Vector* vec, void* elem);
void VectorSort(Vector* vec);

void VectorReverse(Vector* vec);

#endif  
