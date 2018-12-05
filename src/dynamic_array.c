#include <stdio.h>
#include <stdlib.h>


dyn_array *resize_array(dyn_array *array, int new_size) {
  array.low_water_mark = new_size/4;
  array = realloc(array, new_size);
  if(array == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

dyn_array *add_element_to_end(dyn_array *array_to_insert_in, element element_to_insert) {
  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in.size == array_to_insert_in.high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    return resize_array(array_to_insert_in, 2 * array_to_insert_in.size);
  }
  /* If array is not resized then NULL is returned */
  return NULL;
}
