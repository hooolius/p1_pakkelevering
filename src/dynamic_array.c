#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dynamic_array.h"
struct a_node{
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

typedef struct a_node node;

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

dyn_array_heap *resize_array_h(dyn_array_heap *array, int new_size);

/* HEAP FUNCTIONS */
dyn_array_heap *make_dyn_array_h(int min_capacity) {
  dyn_array_heap *array = calloc(1, sizeof(dyn_array_heap));
  array->heaps = calloc(min_capacity, sizeof(pairing_heap) * 2 * min_capacity);
  array->min_capacity = min_capacity;
  array->low_water_mark = min_capacity;
  array->high_water_mark = 2 * min_capacity;
  array->items = 0;
  return array;
}

dyn_array_heap *resize_array_h(dyn_array_heap *array, int new_size) {
  array->low_water_mark = (int)ceil(new_size/4);
  array->high_water_mark = new_size;
  array->heaps = realloc(array->heaps, new_size * sizeof(heap_elem));
  if(array->heaps == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

dyn_array_heap *add_heap_to_end_h(dyn_array_heap *array_to_insert_in, pairing_heap heap_to_insert) {
  dyn_array_heap *res = array_to_insert_in;
  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    res = resize_array_h(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->heaps[array_to_insert_in->items] = heap_to_insert;
  ++array_to_insert_in->items;
  /* If array is not resized then NULL is returned */
  return res;
}

void ensure_capacity_h(dyn_array_heap *array, int capacity) {
  array->min_capacity = capacity;
}

dyn_array_heap *delete_heap_h(dyn_array_heap *array, pairing_heap heap_to_delete) {
  dyn_array_heap *res = array;
  for (int i = 0; i < array->items; ++i) {
    if(array->heaps[i].proot == heap_to_delete.proot) {
      array->heaps[i] = array->heaps[array->items];
      --array->items;
    }
  }
  if(array->items < array->low_water_mark) {
    res = resize_array_h(res, MAX((int)ceil(array->high_water_mark/4), array->min_capacity));
  }
  return res;
}

dyn_array_heap *find_heap_h(dyn_array_heap *array, pairing_heap heap_to_find) {
  dyn_array_heap *res;
  for (int i = 0; i < array->items; ++i) {
    if(array->heaps[i].proot == heap_to_find.proot) {
      res = &array->heaps[i];
    }
  }
  return res;
}
