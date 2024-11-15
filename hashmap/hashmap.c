#include "hashmap.h" 

#include <stdlib.h>
#include <string.h>


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

bool HashmapInsert(Hashmap* map, char* key, void* value) {
  if (!key) return false;
  if (!value) return false; 

  HashEntry entry;
  HashEntry ext = { 
    .hash = map->hash(key), 
    .data = value,
    .psl = 0,
  };
  HashEntry baz = { 0 };
  int index = __toIndex(ext.hash, map->cap);
  
  for (int i = 0; i < map->cap; ++i, ext.psl++) {
    entry = map->arr[(index+i) % map->cap];
    // if empty, insert 
    // else, if psl > entry psl
    //    swap held entry with array entry
    //    psl = new entry psl
    if (!entry.data) {
      memcpy(&entry, &ext, sizeof(HashEntry));
      map->load++;
      if (map->load > (int) ((float) map->cap)*HASHMAP_LOAD_FACTOR) {
        //TODO: check if resize needed
      }
      return true;
    }

    if (ext.psl > entry.psl) {
      memcpy(&baz, &entry, sizeof(HashEntry));
      memcpy(&entry, &ext, sizeof(HashEntry));
      memcpy(&ext, &baz, sizeof(HashEntry));
    }
  }
  // if no insert occured, return false
  return false;
}

// seems kinda unsafe ngl
void* HashmapIndex(Hashmap* map, char* key, void* value) {
  return map->arr[__toIndex(map->hash(key), map->cap)].data;
}

void* HashmapRemove(Hashmap* map, char* key) {
  if (!map) return NULL;
  if (!key) return NULL;
  
  int idx = __toIndex(map->hash(key), map->cap);
  void* ptr = map->arr[idx].data;
  //map->arr[idx] = NULL;
  memset(map->arr+idx, 0, sizeof(HashEntry));
  // shift up
  return ptr;
}

bool HashmapReplace(Hashmap* map, char* key, void* value) {
  //FIXME: IMPLEMENT THIS
  return false;
}
