#ifndef HASHMAP_H
#define HASHMAP_H

#ifndef HASHMAP_INIT_CAP
#define HASHMAP_INIT_CAP 32
#endif

#ifndef HASHMAP_LOAD_FACTOR
#define HASHMAP_LOAD_FACTOR 0.75
#endif

#include <stdbool.h>
#include <stdint.h>

#define uint64_t unsigned long

typedef struct {  
  uint64_t hash; 
  void* data;
  int psl;
} HashEntry;

typedef struct {
  uint64_t (*hash)(unsigned char*);
  int load;
  int cap;
  HashEntry* arr;
} Hashmap;

//TODO: create HashmapInit for initializing stack-allocated hashmaps
Hashmap* NewHashmap();

bool HashmapInsert(Hashmap* map, char* key, void* value); 
void* HashmapRemove(Hashmap* map, char* key);
bool HashmapReplace(Hashmap* map, char* key, void* value); 

void HashmapFree(Hashmap* map);

#endif
