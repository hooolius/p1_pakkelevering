#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dynamic_array.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/* HEAP FUNCTIONS */
dyn_array *make_dyn_array(int min_capacity, ) {
  dyn_array *array = calloc(min_capacity, sizeof(dyn_array) + sizeof());
  array.min_capacity = min_capacity;
  array.low_water_mark = min_capacity;
  array.high_water_mark = 2 * min_capacity;
  array.items = 0;
  return array;
}

dyn_array *resize_array(dyn_array *array, int new_size) {
  array.low_water_mark = (int)ceil(new_size/4);
  array.high_water_mark = new_size;
  //array.size = new_size;
  array = realloc(array, new_size);
  if(array == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

dyn_array *add_element_to_end(dyn_array *array_to_insert_in, element elem_to_insert) {
  dyn_array *res = array_to_insert_in;
  ++items;
  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in.items >= array_to_insert_in.high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    res = resize_array(array_to_insert_in, 2 * array_to_insert_in.high_water_mark);
  }
  ++array_to_insert_in.items;
  /* If array is not resized then NULL is returned */
  return NULL;
}

void ensure_capacity(dyn_array *array, int capacity) {
  array.min_capacity = capacity;
}

dyn_array *delete_element(dyn_array *array, element elem_to_delete) {
  dyn_array *res = array;
  for (int i = 0; i < array.items; ++i) {
    if(array.elements[i] == elem_to_delete) {
      array.elements[i] = array.elements[items];
      --items;
    }
  }
  if(array.items < array.low_water_mark) {
    res = resize_array(MAX(2*high_water_mark, array.min_capacity));
  }
  return res;
}

dyn_array *find_element(dyn_array *array, element elem_to_find) {
  dyn_array *res;
  for (int i = 0; i < array.items; ++i) {
    if(array.elements[i] == elem_to_find) {
      res = &array.elements[i];
    }
  }
  return res;
}

/* NODE FUNCTIONS */
dyn_array *make_dyn_array(int min_capacity, ) {
  dyn_array *array = calloc(min_capacity, sizeof(dyn_array) + sizeof());
  array.min_capacity = min_capacity;
  array.low_water_mark = min_capacity;
  array.high_water_mark = 2 * min_capacity;
  array.items = 0;
  return array;
}

dyn_array *resize_array(dyn_array *array, int new_size) {
  array.low_water_mark = (int)ceil(new_size/4);
  array.high_water_mark = new_size;
  //array.size = new_size;
  array = realloc(array, new_size);
  if(array == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

dyn_array *add_element_to_end(dyn_array *array_to_insert_in, element elem_to_insert) {
  dyn_array *res = array_to_insert_in;
  ++items;
  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in.items >= array_to_insert_in.high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    res = resize_array(array_to_insert_in, 2 * array_to_insert_in.high_water_mark);
  }
  ++array_to_insert_in.items;
  /* If array is not resized then NULL is returned */
  return NULL;
}

void ensure_capacity(dyn_array *array, int capacity) {
  array.min_capacity = capacity;
}

dyn_array *delete_element(dyn_array *array, element elem_to_delete) {
  dyn_array *res = array;
  for (int i = 0; i < array.items; ++i) {
    if(array.elements[i] == elem_to_delete) {
      array.elements[i] = array.elements[items];
      --items;
    }
  }
  if(array.items < array.low_water_mark) {
    res = resize_array(MAX(2*high_water_mark, array.min_capacity));
  }
  return res;
}

dyn_array *find_element(dyn_array *array, element elem_to_find) {
  dyn_array *res;
  for (int i = 0; i < array.items; ++i) {
    if(array.elements[i] == elem_to_find) {
      res = &array.elements[i];
    }
  }
  return res;
}
