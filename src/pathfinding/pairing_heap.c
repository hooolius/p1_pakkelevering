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
void make_root(heap_node *hnode);

pairing_heap init_heap();

/* heap node functions */

heap_node init_node(node *element) {
    heap_node hnode;
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
    pheap.detached = *make_dyn_array_h(10);

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

heap_node *find(pairing_heap *pheap,node *element) {
    heap_node *ptr = pheap->FORE->next;
    while (ptr != pheap->AFT) {
        if (ptr->element->id == element->id) {
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

int compare(node *element_a, node *element_b) {
    return (element_b->f - element_a->f);
}

heap_node *merge(heap_node *hnode_a, heap_node *hnode_b) {
    if (compare(hnode_a->element, hnode_b->element) < 0) {
        add_child(hnode_b, hnode_a);
        return hnode_b;
    }
    else {
        add_child(hnode_a, hnode_b);
        return hnode_a;
    }
}

void merge_with_root(pairing_heap *pheap,heap_node *hnode) {
    if (pheap->root == NULL) {
        pheap->root = hnode;
    }
    else {
        pheap->root = merge(pheap->root, hnode);
    }
}

heap_node insert(pairing_heap *pheap, node *element) {
    heap_node hnode = init_node(element);
    merge_with_root(pheap,&hnode);
    set_next(pheap->AFT->prev, &hnode);
    set_next(&hnode, pheap->AFT);
    pheap->size++;
    return hnode;
}

void add_element(pairing_heap *pheap, node *element
) {
    insert(pheap, element);
}

// locator add_tracked(node *element) {
// heap_node hnode = init_node(element);
// locator l = init_locator(hnode);
// return l;
// }

dyn_array_heap move_children(dyn_array_heap *detached, heap_node *hnode) {
    heap_node *ptr = hnode->child;
    hnode->child = NULL;
    while (ptr != NULL) {
        heap_node *right = ptr->sib_right;
        make_root(ptr);
        add_heap_to_end_h(detached, *ptr);
        ptr = right;
    }
    return *detached;
}

heap_node merge_detached(dyn_array_heap *detached) {
    while (detached->items > 1) {
        heap_node a = detached->heap_nodes[0];
        heap_node b = detached->heap_nodes[1];
        add_heap_to_end_h(detached, *merge(&a, &b));
    }
    return (detached->heap_nodes[0]);
}

void decrease_priority(pairing_heap *pheap, heap_node *hnode, node *element) {
    hnode->element = element;
    if (hnode->child != NULL) {
        move_children(&pheap->detached, hnode);
        heap_node merged = merge_detached(&pheap->detached);
        pheap->root = merge(pheap->root, &merged);
        make_root(pheap->root);
    }
}

void increase_priority(pairing_heap *pheap, heap_node *hnode, node *element) {
    hnode->element = element;
    if (hnode != pheap->root) {
        remove_from_chain(hnode);
        hnode->sib_left = hnode->sib_right = NULL;
        pheap->root = merge(pheap->root, hnode);
        make_root(pheap->root);
    }
}

void update(pairing_heap *pheap, heap_node *hnode, node *element) {
    if (compare(hnode->element, element) < 0) {
        increase_priority(pheap, hnode, element);
    }
    else if (compare(hnode->element, element) > 0) {
        decrease_priority(pheap, hnode, element
        );
    }
    else {
        hnode->element = element;
    }
}

node remove_from_heap(pairing_heap *pheap, heap_node *hnode) {
    if (hnode->child == NULL) {
        remove_from_chain(hnode);
    }
    else {
        move_children(&pheap->detached, hnode);
        heap_node merged = merge_detached(&pheap->detached);
        if (hnode == pheap->root) {
            pheap->root = &merged;
        }
        else {
            remove_from_chain(hnode);
            pheap->root = merge(pheap->root, &merged);
        }
    }
    mark_deleted(hnode);
    set_next(hnode->prev, hnode->next);
    pheap->size--;
    return *hnode->element;
}

int bool_remove(pairing_heap *pheap, node *element) {
    heap_node *node = find(pheap, element);
    if (node == NULL) {
        remove_from_heap(pheap, node);
        return 1;
    }
    return 0;
}

node extract_min(pairing_heap pheap) {
    if (is_empty(pheap)) {
        perror("Error, heap is empty");
        exit(EXIT_FAILURE);
    }
    else {
        return remove_from_heap(pheap, pheap->root);
    }//TODO: Pointer or not?
}
