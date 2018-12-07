#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pairing_heap.h"
struct a_node{
  int id;
  float lat;
  float lon;
  double g;
  double h;
  double f;
  int is_active;
};

typedef struct a_node node;
#include "dynamic_array.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/* HEAP FUNCTIONS */
dyn_array_heap *make_dyn_array_h(int min_capacity) {
  dyn_array_heap *array = calloc(1, sizeof(dyn_array_heap));
  array->heap_elems = calloc(min_capacity, sizeof(heap_elem) * 2 * min_capacity);
  array->min_capacity = min_capacity;
  array->low_water_mark = min_capacity;
  array->high_water_mark = 2 * min_capacity;
  array->items = 0;
  return array;
}

dyn_array_heap *resize_array_h(dyn_array_heap *array, int new_size) {
  array->low_water_mark = (int)ceil(new_size/4);
  array->high_water_mark = new_size;
  array->heap_elems = realloc(array->heap_elems, new_size * sizeof(heap_elem));
  if(array->heap_elems == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

dyn_array_heap *add_heap_to_end_h(dyn_array_heap *array_to_insert_in, heap_elem heap_to_insert) {
  dyn_array_heap *res = array_to_insert_in;
  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    res = resize_array_h(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->heap_elems[array_to_insert_in->items] = heap_to_insert;
  ++array_to_insert_in->items;
  /* If array is not resized then NULL is returned */
  return res;
}

void ensure_capacity_h(dyn_array_heap *array, int capacity) {
  array->min_capacity = capacity;
}

dyn_array_heap *delete_heap_h(dyn_array_heap *array, heap_elem heap_to_delete) {
  dyn_array_heap *res = array;
  for (int i = 0; i < array->items; ++i) {
    if(array->heap_elems[i].id == heap_to_delete.id) {
      array->heap_elems[i] = array->heap_elems[array->items];
      --array->items;
    }
  }
  if(array->items < array->low_water_mark) {
    res = resize_array(res, MAX((int)ceil(array->high_water_mark/4), array->min_capacity));
  }
  return res;
}

dyn_array_heap *find_heap_h(dyn_array_heap *array, heap_elem heap_to_find) {
  dyn_array_heap *res;
  for (int i = 0; i < array->items; ++i) {
    if(array->heap_elems[i] == heapto_find) {
      res = &array->heap_elems[i];
    }
  }
  return res;
}

/* NODE FUNCTIONS */
dyn_array_node *make_dyn_array_n(int min_capacity) {
  dyn_array_node *array = calloc(1, sizeof(dyn_array_node));
  array->nodes = calloc(min_capacity, sizeof(node) * 2 * min_capacity);
  array->min_capacity = min_capacity;
  array->low_water_mark = min_capacity;
  array->high_water_mark = 2 * min_capacity;
  array->items = 0;
  return array;
}

dyn_array_node *resize_array_n(dyn_array_node *array, int new_size) {
  array->low_water_mark = (int)ceil(new_size/4);
  array->high_water_mark = new_size;
  array->nodes = realloc(array->nodes, new_size * sizeof(node));
  if(array->nodes == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

dyn_array_node *add_node_to_end_n(dyn_array_node *array_to_insert_in, node node_to_insert) {
  dyn_array_node *res = array_to_insert_in;

  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    res = resize_array_n(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->nodes[array_to_insert_in->items] = node_to_insert;
  ++array_to_insert_in->items;
  /* If array is not resized then NULL is returned */
  return res;
}

void ensure_capacity_n(dyn_array_node *array, int capacity) {
  array->min_capacity = capacity;
}

dyn_array_node *delete_node_n(dyn_array_node *array, node node_to_delete) {
  dyn_array_node *res = array;
  for (int i = 0; i < array->items; ++i) {
    if(array->nodes[i].id == node_to_delete.id) {
      array->nodes[i] = array->nodes[array->items];
      --array->items;
    }
  }
  if(array->items < array->low_water_mark) {
    res = resize_array_n(res, MAX((int)ceil(array->high_water_mark/4), array->min_capacity));
  }
  return res;
}

dyn_array_node *find_node_n(dyn_array_node *array, node node_to_find) {
  dyn_array_node *res;
  for (int i = 0; i < array->items; ++i) {
    if(array->nodes[i] == node_to_find.id) {
      res = &array->nodes[i];
    }
  }
  return res;
}
