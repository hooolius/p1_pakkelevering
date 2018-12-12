#include "pairing_heap.h"

/* function prototypes */
void make_root(heap_node *hnode);
pairing_heap init_heap();

/* heap node functions */

heap_node init_node(node *element, double value) {
  heap_node hnode;
  hnode.value = value;
  hnode.element = element;
  make_root(&hnode);

  return hnode;
}

void make_root(heap_node *hnode) {
  hnode->sib_left = hnode;
  hnode->sib_right = NULL;
  return;
}

void set_left(heap_node *hnode, heap_node *sib_ptr) {
  hnode->sib_left = sib_ptr;
  sib_ptr->sib_right = hnode;
}

void set_next(heap_node *hnode, heap_node *next_ptr) {
  hnode->next = next_ptr;
  next_ptr->prev = hnode;
}

int is_leftmost_child(heap_node *hnode) {
  return hnode->sib_left == hnode;
}

int is_rightmost_child(heap_node *hnode) {
  return hnode->sib_right == NULL;
}

void mark_deleted(heap_node *hnode) {
  hnode->sib_left = NULL;
}

int is_deleted(heap_node *hnode) {
  return hnode->sib_left == NULL;
}

void add_child(heap_node *hnode, heap_node *child) {
  if (hnode->child == NULL) {
    hnode->child = child;
    child->sib_left = hnode;
  }
  else if (is_rightmost_child(child)) {
    set_left(hnode, child);
  }
  else {
    set_left(hnode->child->sib_right, child);
    set_left(child, hnode->child);
  }
}

void remove_from_chain(heap_node *hnode) {
  if (is_leftmost_child(hnode)) {
    hnode->sib_left->child = hnode->sib_right;
  }
  else {
    hnode->sib_left->sib_right = hnode->sib_right;
  }
  if (is_rightmost_child(hnode)) {
    hnode->sib_right->sib_left = hnode->sib_left;
  }
}

/* heap functions */

pairing_heap init_heap() {
  pairing_heap pheap;
  heap_node nFORE;
  heap_node nAFT;

  pheap.size = 0;
  pheap.root = NULL;

  set_next(&nFORE, &nAFT);

  mark_deleted(&nFORE);
  pheap.FORE = &nFORE;
  mark_deleted(&nAFT);
  pheap.AFT = &nAFT;
  
  return pheap;
}

int is_empty(pairing_heap *pheap) {
  return (pheap->root == NULL);
}

void heap_reinit(pairing_heap *pheap) {
  pheap->size = 0;
  pheap->root = NULL;
  set_next(pheap->FORE, pheap->AFT);
}

node min(pairing_heap *pheap) {
  if (is_empty(pheap)) {
    perror("Error, heap is empty");
    exit(EXIT_FAILURE);
  }
  //TODO: pointer or not?
  return *pheap->root->element;
}

heap_node *find(pairing_heap *pheap, node *element) {
  heap_node *ptr = pheap->FORE->next;
  while (ptr != pheap->AFT){
    if(ptr->element->id == element->id) {
      return ptr;
    }
    ptr = ptr->next;
  }
  return NULL;
}

node get_equivalent_element(pairing_heap *pheap, node *target) {
  heap_node *node = find(pheap, target);
  if (node != NULL) {
    return *node->element;
  }
  else {
    perror("Error, target not found");
    exit(EXIT_FAILURE);
  }
}






