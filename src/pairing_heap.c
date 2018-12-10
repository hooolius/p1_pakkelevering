#include <stdio.h>
#include <stdlib.h>
#include "pairing_heap.h"

pairing_heap merge_pairs(pairing_heap heap, dyn_array_heap subheaps[]);

void heap_init(pairing_heap heap) {
  dyn_array_heap *subheap_arr;
  subheap_arr = make_dyn_array_h(2);

  heap.size = 0;
  heap.proot = NULL;
  heap.subheaps = subheap_arr;
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
    add_heap_to_end_h(heap1.subheaps, heap2);
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
    add_heap_to_end_h(heap2.subheaps, heap1);
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

void insert_elem(pairing_heap heap, heap_elem elem, double value) {
  heap.size++;
  pairing_heap addition;
  heap_elem *pelem = &elem;

  pelem->pleft_child = NULL;
  pelem->pprev_sibling = NULL;
  pelem->pnext_sibling = NULL;
  pelem->value = value;

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
    merge_pairs(heap, heap.subheaps);
  }
}

pairing_heap merge_pairs(pairing_heap heap, dyn_array_heap subheaps[]) {
  pairing_heap sub1, sub2;
  if (heap.subheaps->items == 0) {
    return heap;
  }
  else if (heap.subheaps->items == 1) {
    return merge(heap, subheaps->heaps[0]);
  }
  else {
    sub1 = subheaps->heaps[0];
    sub2 = subheaps->heaps[1];
    delete_heap_h(subheaps->heaps, sub1);
    delete_heap_h(subheaps->heaps, sub2);
    return merge(merge(sub1, sub2), merge_pairs(heap, subheaps));
  }
}
