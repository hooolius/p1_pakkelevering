/* dynamic_array.h - made with inspiration from
"A Practical Guide to Data Structures and Algorithms using Java" */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pairing_heap.h"

struct node{
  int id;
  double lat;
  double lon;
  double g;
  double h;
  double f;
  int is_active;
  int p1;
  int p2;
  int p3;
  int p4;
  int p5;
  int p6;
};

typedef struct node node;

struct dyn_array_node {
  int low_water_mark;
  int high_water_mark;
  int min_capacity;
  int number_of_elements;
  int items;
  node *nodes;
};

typedef struct dyn_array_node dyn_array_node;

/* HEAP FUNCTIONS */
/* Makes a empty array */
dyn_array_heap *make_dyn_array_h(int size);

/* Not implemented yet */
void trim_to_size_h();

/* Maybe implemented */
void ensure_capacity_h(dyn_array_heap *array, int capacity);

/* Implemented */
dyn_array_heap *resize_array_h(dyn_array_heap *array, int new_size);

/* Implemented */
dyn_array_heap *add_heap_to_end_h(dyn_array_heap *array_to_insert_in, pairing_heap heap_to_insert);
/* Implemented */
dyn_array_heap *delete_heap_h(dyn_array_heap *array, pairing_heap heap_to_delete);
/* Not implemented yet */
dyn_array_heap *find_heap_h(dyn_array_heap *array, pairing_heap heap_to_find);

// NODE FUNCTIONS
dyn_array_node *make_dyn_array_n(int size);

/* Not implemented yet */
void trim_to_size_n();

/* Maybe implemented */
void ensure_capacity_n(dyn_array_node *array, int capacity);

/* Implemented */
dyn_array_node *resize_array_n(dyn_array_node *array, int new_size);

/* Implemented */
dyn_array_node *add_node_to_end_n(dyn_array_node *array_to_insert_in, node node_to_insert);
/* Implemented */
dyn_array_node *delete_node_n(dyn_array_node *array, node node_to_delete);
/* Not implemented yet */
dyn_array_node *find_node_n(dyn_array_node *array, node node_to_find);
