#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pairing_heap.h"


int main(void) {
  pairing_heap heap;
  heap_init(heap);
  heap_elem elem;
  insert_elem(heap, elem, 2.0);
  assert(heap.proot->value == 2.0);
  printf("insert works, value: %lf", heap.proot->value);

}
