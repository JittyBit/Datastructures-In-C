#include <stdio.h>
#include <assert.h>

#include "hashmap.h"

int main() {
  printf("hashmap tests\n");

  Hashmap* map = NewHashmap();
  if (!map) {
    fprintf(stderr, "ERROR INITIALIZING HASHMAP\n");
  }

  if (!HashmapInsert(map, "key0", (void*) 10)) {
    assert(false && "COULD NOT INSERT ELEMENT 0");
  }
  if (!HashmapInsert(map, "key1", (void*) 20)) {
    assert(false && "COULD NOT INSERT ELEMENT 1");
  }
  if (!HashmapInsert(map, "key2", (void*) 30)) {
    assert(false && "COULD NOT INSERT ELEMENT 2");
  }

  long val0 = (long) HashmapRemove(map, "key0");
  HashmapInsert(map, "key00", (void*) 15);
  long val1 = (long) HashmapRemove(map, "key1");
  HashmapInsert(map, "key11", (void*) 25);
  long val2 = (long) HashmapRemove(map, "key2");
  HashmapInsert(map, "key22", (void*) 35);

  printf("map[\"key0\"] = %lu\n", val0);
  printf("map[\"key1\"] = %lu\n", val1);
  printf("map[\"key2\"] = %lu\n", val2);

  puts("");

  printf("map[\"key00\"] = %lu\n", HashmapRemove(map, "key00"));
  printf("map[\"key11\"] = %lu\n", HashmapRemove(map, "key11"));
  printf("map[\"key22\"] = %lu\n", HashmapRemove(map, "key22"));

  HashmapFree(map);

  return 0;
}
