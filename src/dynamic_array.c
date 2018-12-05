#include <stdio.h>
#include <stdlib.h>
##include <math.h>


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

dyn_array *add_element_to_end(dyn_array *array_to_insert_in, element element_to_insert) {
  dyn_array *res = array_to_insert_in;
  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in.size == array_to_insert_in.high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    res = resize_array(array_to_insert_in, 2 * array_to_insert_in.size);
  }
  ++array_to_insert_in.items;
  /* If array is not resized then NULL is returned */
  return NULL;
}

void ensure_capacity(dyn_array *array, int capacity) {
  array.min_capacity = capacity;
}
