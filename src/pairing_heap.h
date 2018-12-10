/* pairing_heap.h - pairing heap implementation for C, to be used in our P1 
 * project at AAU. Designed for use in our A* implementation. */
#include "dynamic_array.h"

typedef struct heap_elem heap_elem;
typedef struct pairing_heap pairing_heap;


struct heap_elem {
  double value;
  heap_elem *pleft_child;
  heap_elem *pprev_sibling;
  heap_elem *pnext_sibling;
};

struct pairing_heap {
  int size;
  heap_elem *proot;
  dyn_array_heap *subheaps;
};

//initialize heap
pairing_heap heap_init(pairing_heap heap);
// returns the lowest value in the heap
heap_elem find_min(pairing_heap heap);
// merges two heaps together
pairing_heap merge(pairing_heap heap1, pairing_heap heap2);
// returns and deletes the min element in a heap
heap_elem extract_min(pairing_heap heap);
// deletes the minimum element of the heap
void delete_min(pairing_heap heap);
// inserts an element into a heap 
void insert_elem(pairing_heap heap, heap_elem elem);
// removes a node from the heap 
void delete_elem(int i, pairing_heap heap);
// redefines the element i to n 
void decrease_key(int i, int n, pairing_heap heap);
