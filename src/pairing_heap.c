#include <stdio.h>
#include <stdlib.h>
#include "pairing_heap.h"

heap_elem *find_min(pairing_heap heap) {
  if (heap.proot == NULL) {
    perror("Error, heap is empty");
    exit(EXIT_FAILURE);
  }
  else {
    return heap.proot;
  }
}

pairing_heap merge(pairing_heap heap1, pairing_heap heap2) {
  heap_elem *ptemp;
  if (heap1.proot == NULL && heap2.proot == NULL) {
    perror("Error, both heaps are empty");
    exit(EXIT_FAILURE);
  }
  else if (heap1.proot == NULL) {
    return heap2;
  }
  else if (heap2.proot == NULL) {
    return heap1;
  }
  else if (heap1.proot->value < heap2.proot->value) {
    if (heap1.proot->pleft_child == NULL) {
      heap1.proot->pleft_child = heap2.proot;
    }
    else if (heap1.proot->pleft_child->pprev_sibling == NULL) {
      heap1.proot->pleft_child->pprev_sibling = heap2.proot;
    }
    else {
      ptemp = heap1.proot->pleft_child;
      heap1.proot->pleft_child = heap2.proot;
      heap1.proot->pleft_child->pnext_sibling = ptemp;
    }
  }
  else {
    //return ?
  }
}
