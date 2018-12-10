#include <stdio.h>
#include <stdlib.h>
#include "pairing_heap.h"
#include "dynamic_array.h"

pairing_heap merge_pairs(pairing_heap heap, pairing_heap subheaps[]);

pairing_heap heap_init(pairing_heap heap) {
  dyn_array_heap *subheap_arr;
  subheap_arr = make_dyn_array_h(2);

  heap.size = 0;
  heap.proot = NULL;
  heap.subheaps = subheap_arr;
  
  return heap;
}

heap_elem find_min(pairing_heap heap) {
  if (heap.proot == NULL) {
    perror("Error, heap is empty");
    exit(EXIT_FAILURE);
  }
  else {
    return *heap.proot;
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
    heap1.subheaps[++heap1.subheaps->items] = heap2;
    if (heap1.proot->pleft_child == NULL) {
      heap1.proot->pleft_child = heap2.proot;
      return heap1;
    }
    else if (heap1.proot->pleft_child->pprev_sibling == NULL) {
      heap1.proot->pleft_child->pprev_sibling = heap2.proot;
      return heap1;
    }
    else {
      ptemp = heap1.proot->pleft_child;
      heap1.proot->pleft_child = heap2.proot;
      heap1.proot->pleft_child->pnext_sibling = ptemp;
      return heap1;
    }
  }
  else {
    heap2.subheaps->subheaps[++heap1.subheaps->size_subheaps] = heap1;
    if (heap2.proot->pleft_child == NULL) {
      heap2.proot->pleft_child = heap1.proot;
      return heap2;
    }
    else if (heap2.proot->pleft_child->pprev_sibling == NULL) {
      heap2.proot->pleft_child->pprev_sibling = heap1.proot;
      return heap2;
    }
    else {
      ptemp = heap2.proot->pleft_child;
      heap2.proot->pleft_child = heap1.proot;
      heap2.proot->pleft_child->pnext_sibling = ptemp;
      return heap2;
    }
  }
}

void insert_elem(pairing_heap heap, heap_elem elem) {
  heap.size++;
  pairing_heap addition;
  heap_elem *pelem = &elem;

  pelem->pleft_child = NULL;
  pelem->pprev_sibling = NULL;
  pelem->pnext_sibling = NULL;

  if (heap.proot == NULL) {
    heap.proot = pelem;
  }
  else {
    addition.proot = pelem;
    heap = merge(heap, addition);
  }
}

heap_elem extract_min(pairing_heap heap) {
  heap_elem min;
  min = find_min(heap);
  delete_min(heap);
  return min;
}

void delete_min(pairing_heap heap) {
  if (heap.proot == NULL) {
    perror("Error, heap is empty");
    exit(EXIT_FAILURE);
  } 
  else {
    merge_pairs(heap, heap.subheaps->subheaps);
  }
}

pairing_heap merge_pairs(pairing_heap heap, pairing_heap subheaps[]) {
  if (heap.subheaps->size_subheaps == 0) {
    return heap;
  }
  else if (heap.subheaps->size_subheaps == 1) {
    return merge(heap, subheaps[0]);
  }
  else {
    return merge((subheaps[0], subheaps[1]), merge_pairs(heap, subheaps));
  }
}
//lav helper function til merge_pairs, så den kører rekursivt?
