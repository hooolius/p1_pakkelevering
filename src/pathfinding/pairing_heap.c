#include <stdio.h>
#include <stdlib.h>

#ifndef pairing_heap_h
#define pairing_heap_h

#include "pairing_heap.h"

#endif

#ifndef dynamic_array_h
#define dynamic_array_h

#include "../libs/dynamic_array.h"

#endif

/* function prototypes */
/**
 * @brief Initialises a new heap node
 *
 * @param[in] element The element the new node should hold
 *
 * @return The initialised heap node
 */
heap_node *init_node(node *element);
/**
 * @brief Makes a node the root of it's own tree, by having it's sib_left point to itself
 *
 * @param[out] hnode The node to make root
 */
void make_root(heap_node *hnode);
/**
 * @brief Sets a heap node as the left sibling of another heap node
 *
 * @param[out] hnode The heap node to add a left sibling to
 * @param[in] sib_ptr The left sibling to add to another heap_node
 */
void set_left(heap_node *hnode, heap_node *sib_ptr);
/**
 * @brief Sets a heap node as the next element in the iteration order
 *
 * @param[out] hnode The heap node that should be prior to next_ptr
 * @param[in] next_ptr The heap node to add as the next element in the iteration order
 */
void set_next(heap_node *hnode, heap_node *next_ptr);
/**
 * @brief Checks whether or not a heap node is the leftmost child of it's parent
 *
 * @param hnode[in] The heap node to check
 *
 * @return 1 if the heap node is the leftmost child, otherwise 0
 */
int is_leftmost_child(heap_node *hnode);
/**
 * @brief Checks whether or not a heap node is the rightmost child of it's parent
 *
 * @param hnode[in] The heap node to check
 *
 * @return 1 if the heap node is the rightmost child, otherwise 0
 */
int is_rightmost_child(heap_node *hnode);
/**
 * @brief Marks a heap node as deleted, by setting it's sib_left pointer to NULL
 *
 * @param[out] hnode to mark deleted
 */
void mark_deleted(heap_node *hnode);
/**
 * @brief Adds a child to a heap node
 *
 * @param[out] hnode The heap node to add the child node to
 * @param[in] child The child node to add to hnode
 */
void add_child(heap_node *hnode, heap_node *child);
/**
 * @brief Removes a node from the tree
 *
 * @param[in] hnode The node to remove from the tree
 */
void remove_from_chain(heap_node *hnode);
/**
 * @brief Checks if a heap is empty
 *
 * @param[in] pheap The heap to check
 *
 * @return 1 if the heap is empty, 0 otherwise
 */
int is_empty(pairing_heap *pheap);
/**
 * @brief Finds the minimum value in a heap. This is the root of the heap.
 *
 * @param[in] pheap The heap to find the root of
 *
 * @return The root of the input heap
 */
node min(pairing_heap *pheap);
/**
 * @brief Searches for an element in all nodes of the input heap, by searching the iteration list
 *
 * @param[in] pheap The heap to search for the element in
 * @param[in] element The element to search for
 *
 * @return If the element is found, a pointer to the node holding the element, otherwise NULL
 */
heap_node *find(pairing_heap *pheap, node *element);
/**
 * @brief Compares the f values of two elements
 *
 * @param[in] element_a The first element
 * @param[in] element_b The second element
 *
 * @return A negative value if element_a is larger, a positive value if element_b is larger, or 0 if they are equal
 */
int compare(node *element_a, node *element_b);
/**
 * @brief Merges two heap trees
 *
 * @param[in] hnode_a The first heap tree
 * @param[in] hnode_b The second heap tree
 *
 * @return The merged tree
 */
heap_node *merge(heap_node *hnode_a, heap_node *hnode_b);
/**
 * @brief Merges a heap node into a heap;
 *
 * @param[out] pheap The heap to merge the heap node with
 * @param[in] hnode The heap node to merge into the heap
 */
void merge_with_root(pairing_heap *pheap, heap_node *hnode);
/**
 * @brief Inserts an element into a heap
 *
 * @param[out] pheap The heap to insert the new element into
 * @param[in] element The element to insert into the heap
 *
 * @return A pointer to a new heap node holding the input element
 */
heap_node *insert(pairing_heap *pheap, node *element);
/**
 * @brief Moves all the children of a heap node into the detached queue for later use
 *
 * @param[in] detached The detached queue to move the children to
 * @param[in] hnode The heap node to remove children from
 *
 * @return A pointer to the detached queue
 */
dyn_array_heap *move_children(dyn_array_heap *detached, heap_node *hnode);
/**
 * @brief Merges all the heap nodes in the detached queue of a heap into a new tree
 *
 * @param[in] detached The detached queue to merge all nodes of
 *
 * @return A pointer to the new tree containing all the merged nodes
 */
heap_node *merge_detached(dyn_array_heap *detached);
/**
 * @brief Extracts and removes the last element of the detached queue
 *
 * @param[in] detached The detached queue to extract from
 *
 * @return A pointer to the extracted element
 */
heap_node *dequeue(dyn_array_heap *detached);
/**
 * @brief Removes an element from the heap
 *
 * @param[out] pheap The heap to remove an element from
 * @param[in] hnode The element to remove
 *
 * @return A pointer to the removed element
 */
node *remove_from_heap(pairing_heap *pheap, heap_node *hnode);

heap_node *init_node(node *element) {
  heap_node *hnode = calloc(1, sizeof(heap_node));
  hnode->element = element;
  hnode->child = NULL;
  hnode->next = NULL;
  hnode->prev = NULL;
  hnode->sib_left = NULL;
  hnode->sib_right = NULL;
  make_root(hnode);

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

void add_child(heap_node *hnode, heap_node *child) {
  if (hnode->child == NULL) {
    hnode->child = child;
    child->sib_left = hnode;
  } else if (is_rightmost_child(hnode->child)) {
    set_left(child, hnode->child);
  } else {
    set_left(hnode->child->sib_right, child);
    set_left(child, hnode->child);
  }
}

void remove_from_chain(heap_node *hnode) {
  if (is_leftmost_child(hnode)) {
    hnode->sib_left->child = hnode->sib_right;
  } else {
    hnode->sib_left->sib_right = hnode->sib_right;
  }
  if (!is_rightmost_child(hnode)) {
    hnode->sib_right->sib_left = hnode->sib_left;
  }
}

/* heap functions */

pairing_heap *init_heap() {
  pairing_heap *pheap = calloc(1, sizeof(pairing_heap));
  heap_node *nFORE = init_node(NULL);
  heap_node *nAFT = init_node(NULL);
  pheap->detached = make_dyn_array_h(10);

  pheap->size = 0;
  pheap->root = NULL;
  pheap->FORE = *nFORE;
  pheap->AFT = *nAFT;
  mark_deleted(&pheap->FORE);
  mark_deleted(&pheap->AFT);

  set_next(&pheap->FORE, &pheap->AFT);

  return pheap;
}

int is_empty(pairing_heap *pheap) {
  return (pheap->size == 0);
}

node min(pairing_heap *pheap) {
  if (is_empty(pheap)) {
    perror("Error, heap is empty");
    exit(EXIT_FAILURE);
  }
  return *pheap->root->element;
}

heap_node *find(pairing_heap *pheap, node *element) {
  heap_node *ptr = pheap->FORE.next;
  while (ptr != &pheap->AFT) {
    if (ptr->element->id == element->id) {
      return ptr;
    }
    ptr = ptr->next;
  }
  return NULL;
}

int heap_contains(pairing_heap *pheap, node *element) {
  if (find(pheap, element) == NULL) {
    return 0;
  } else return 1;
}

int compare(node *element_a, node *element_b) {
  return (element_b->f - element_a->f);
}

heap_node *merge(heap_node *hnode_a, heap_node *hnode_b) {
  if (compare(hnode_a->element, hnode_b->element) < 0) {
    add_child(hnode_b, hnode_a);
    return hnode_b;
  } else {
    add_child(hnode_a, hnode_b);
    return hnode_a;
  }
}

void merge_with_root(pairing_heap *pheap, heap_node *hnode) {
  if (pheap->root == NULL || pheap->size == 0) {
    pheap->root = hnode;
  } else {
    pheap->root = merge(pheap->root, hnode);
  }
}

heap_node *insert(pairing_heap *pheap, node *element) {
  heap_node *hnode = init_node(element);
  merge_with_root(pheap, hnode);
  set_next(pheap->AFT.prev, hnode);
  set_next(hnode, &pheap->AFT);
  pheap->size++;
  return hnode;
}

void add_element(pairing_heap *pheap, node *element) {
  if (element != NULL) {
    insert(pheap, element);
  }
}

dyn_array_heap *move_children(dyn_array_heap *detached, heap_node *hnode) {
  heap_node *ptr = hnode->child;
  hnode->child = NULL;
  while (ptr != NULL) {
    heap_node *right = ptr->sib_right;
    make_root(ptr);
    add_heap_to_end_h(detached, ptr);
    ptr = right;
  }
  return detached;
}

heap_node *merge_detached(dyn_array_heap *detached) {
  while (detached->items > 1) {
    add_heap_to_end_h(detached, merge(dequeue(detached), dequeue(detached)));
  }
  return dequeue(detached);
}

heap_node *dequeue(dyn_array_heap *detached) {
  heap_node *element = detached->heap_nodes[detached->items - 1];
  detached->items--;
  return element;
}

node *remove_from_heap(pairing_heap *pheap, heap_node *hnode) {
  if (hnode->child == NULL /*|| hnode->child->element == NULL*/) {
    remove_from_chain(hnode);
  } else {
    move_children(pheap->detached, hnode);
    heap_node *merged = merge_detached(pheap->detached);
    if (hnode == pheap->root) {
      pheap->root = merged;
    } else {
      remove_from_chain(hnode);
      pheap->root = merge(pheap->root, merged);
    }
  }
  mark_deleted(hnode);
  set_next(hnode->prev, hnode->next);
  pheap->size--;
  if (pheap->size != 0) {
    make_root(pheap->root);
  }
  node *return_node = hnode->element;
  free(hnode);
  return return_node;
}

node *extract_min(pairing_heap *pheap) {
  if (is_empty(pheap)) {
    perror("Error, heap is empty");
    exit(EXIT_FAILURE);
  } else {
    return remove_from_heap(pheap, pheap->root);
  }
}

void clean_heap(pairing_heap *pheap) {
  heap_node *elem = pheap->AFT.prev->prev;
  while (elem != &pheap->FORE) {
    elem->next->child = NULL;
    elem->next->sib_left = NULL;
    elem->next->sib_right = NULL;
    elem->next->next = NULL;
    elem->next->element = NULL;
    free(elem->next);
    elem = elem->prev;
  }
}
