#include "hashmap.h" 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// dbj hashing algorithm
// http://www.cse.yorku.ca/~oz/hash.html
static uint64_t __dbj(unsigned char* string) {
  uint64_t hash = 5381;
  int c;
  while (c = *string++)
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash;
}

static inline int __toIndex(uint64_t hash, int len) { 
  return hash & (len-1); 
}

Hashmap* NewHashmap() { 
  Hashmap* map = (Hashmap*) malloc(sizeof(Hashmap));
  if (!map) return NULL;
  map->load = 0;
  map->cap = HASHMAP_INIT_CAP;
  map->hash = __dbj;
  map->arr = (HashEntry*) calloc(0, sizeof(HashEntry*)*map->cap);
  if (!map->arr) { 
    free(map); return NULL;
  }
  return map;
}

//IMPORTANT: expects the user to have heap allocated the
//           hashmap and the underlying array.
void HashmapFree(Hashmap* map) {
  if (!map) return;
  if (!map->arr) return;
  free(map->arr);
  free(map);
}

//TODO: implement automatic hashmap resizing
bool HashmapInsert(Hashmap* map, char* key, void* value) {
  if (!key) return false;
  if (!value) return false; 

  HashEntry* entry;
  HashEntry ext = { 
    .hash = map->hash(key), 
    .data = value,
    .psl = 0,
  };
  HashEntry baz = { 0 };
  int index = __toIndex(ext.hash, map->cap);
  
  for (int i = 0; i < map->cap; ++i, ++ext.psl) {
    entry = map->arr + ((index+i) % map->cap);
    if (!entry->data) {
      memcpy(entry, &ext, sizeof(HashEntry));
      map->load++;
      if (map->load > (int) ((float) map->cap)*HASHMAP_LOAD_FACTOR) {
        //TODO: check if resize needed
      }
      return true;
    }

    if (ext.psl > entry->psl) {
      memcpy(&baz, entry, sizeof(HashEntry));
      memcpy(entry, &ext, sizeof(HashEntry));
      memcpy(&ext, &baz, sizeof(HashEntry));
    }
  }
  // if no insert occured, return false
  return false;
}

// should account for hash collisions now
void* HashmapIndex(Hashmap* map, char* key) {
  if (!map) return NULL;
  if (!key) return NULL;

  uint64_t hash = map->hash(key);
  int idx = __toIndex(hash, map->cap);
  for (int i = 0; i < map->cap; ++i, ++idx) {
    if (map->arr[idx % map->cap].hash == hash)
      return map->arr[idx % map->cap].data; 
  }
  return NULL;
}

// should be finished?
void* HashmapRemove(Hashmap* map, char* key) {
  if (!map) return NULL;
  if (!key) return NULL;
  
  uint64_t hash = map->hash(key);
  int idx = __toIndex(hash, map->cap);
  for (int i = 0; i < map->cap; ++i, ++idx) {
    if (map->arr[idx % map->cap].hash == hash)
      break;
  }  

  void* ptr = map->arr[idx].data;
  memset(map->arr+idx, 0, sizeof(HashEntry));

  //unsigned long index;
  for (uint32_t i = 0, index = 0; map->arr[index = ((idx+i) % map->cap)].psl > 0; ++i) {
    ((HashEntry*) memcpy(map->arr+index-1,map->arr+index,sizeof(HashEntry)))->psl--;
    memset(map->arr+index,0,sizeof(HashEntry));
  }

  return ptr;
}

bool HashmapReplace(Hashmap* map, char* key, void* value) {
  if (!map) return false;
  if (!key) return false;
  if (!value) return false;

  uint64_t hash = map->hash(key);
  int idx = __toIndex(hash, map->cap);
  for (int i = 0; i < map->cap; ++i, ++idx) {
    if (map->arr[idx % map->cap].hash == hash) {
      map->arr[idx % map->cap].data = value;
      return true;
    }
  }
  return false;
}
