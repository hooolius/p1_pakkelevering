#include <string.h>
#include "dynamic_array.h"

/* HEAP FUNCTIONS */
dyn_array_heap *make_dyn_array_h(int min_capacity) {
  dyn_array_heap *array = calloc(1, sizeof(dyn_array_heap));
  array->heap_nodes = calloc(min_capacity, sizeof(heap_node*) * 2 * min_capacity);
  array->min_capacity = min_capacity;
  array->low_water_mark = min_capacity;
  array->high_water_mark = 2 * min_capacity;
  array->items = 0;
  return array;
}

dyn_array_heap *resize_array_h(dyn_array_heap *array, int new_size) {
  array->low_water_mark = (int)ceil(new_size/4);
  array->high_water_mark = new_size;
  array->heap_nodes = realloc(array->heap_nodes, new_size * sizeof(heap_node));
  if(array->heap_nodes == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

dyn_array_heap *add_heap_to_end_h(dyn_array_heap *array_to_insert_in, heap_node *heap_to_insert) {
  dyn_array_heap *res = array_to_insert_in;
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    res = resize_array_h(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->heap_nodes[array_to_insert_in->items] = heap_to_insert;
  ++array_to_insert_in->items;
  return res;
}

/* NODE FUNCTIONS */
dyn_array_node *make_dyn_array_n(int min_capacity) {
  dyn_array_node *array = calloc(1, sizeof(dyn_array_node));
  array->nodes = (node**)calloc(min_capacity, sizeof(node*) * 2 * min_capacity);
  array->min_capacity = min_capacity;
  array->low_water_mark = min_capacity;
  array->high_water_mark = 2 * min_capacity;
  array->items = 0;
  return array;
}

dyn_array_node *resize_array_n(dyn_array_node *array, int new_size) {
  array->low_water_mark = (int)ceil(new_size/4);
  array->high_water_mark = new_size;
  array->nodes = realloc(array->nodes, new_size * sizeof(node*));
  if(array->nodes == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

dyn_array_node *add_node_to_end_n(dyn_array_node *array_to_insert_in, node *node_to_insert) {
  dyn_array_node *res = array_to_insert_in;
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    res = resize_array_n(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->nodes[array_to_insert_in->items] = node_to_insert;
  array_to_insert_in->items += 1;
  return res;
}

/* Addresses Functions */
dyn_array_address *make_dyn_array_a(int min_capacity) {
  dyn_array_address *array = calloc(1, sizeof(dyn_array_address));
  array->addresses = calloc(min_capacity, sizeof(struct address) * 2 * min_capacity);
  array->min_capacity = min_capacity;
  array->low_water_mark = min_capacity;
  array->high_water_mark = 2 * min_capacity;
  array->items = 0;
  return array;
}

dyn_array_address *resize_array_a(dyn_array_address *array, int new_size) {
  array->low_water_mark = (int)ceil(new_size/4);
  array->high_water_mark = new_size;
  array->addresses = realloc(array->addresses, new_size * sizeof(struct address));
  if(array->addresses == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

dyn_array_address *add_address_to_end_a(dyn_array_address *array_to_insert_in, struct address address_to_insert) {
  dyn_array_address *res = array_to_insert_in;
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    res = resize_array_a(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->addresses[array_to_insert_in->items] = address_to_insert;
  array_to_insert_in->items += 1;
  return res;
}

/* INTEGER Functions */
dyn_array_int *make_dyn_array_i(int min_capacity) {
  dyn_array_int *array = calloc(1, sizeof(dyn_array_int));
  array->integers = calloc(min_capacity, sizeof(int) * 2 * min_capacity);
  array->min_capacity = min_capacity;
  array->low_water_mark = min_capacity;
  array->high_water_mark = 2 * min_capacity;
  array->items = 0;
  return array;
}

dyn_array_int *resize_array_i(dyn_array_int *array, int new_size) {
  array->low_water_mark = (int)ceil(new_size/4);
  array->high_water_mark = new_size;
  array->integers = realloc(array->integers, new_size * sizeof(struct address));
  if(array->integers == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

dyn_array_int *add_int_to_end_i(dyn_array_int *array_to_insert_in, int int_to_insert) {
  dyn_array_int *res = array_to_insert_in;
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    res = resize_array_i(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->integers[array_to_insert_in->items] = int_to_insert;
  array_to_insert_in->items += 1;
  return res;
}
/**
*@brief This function finds a specific address
*@param[in] "dyn_array_address *array" The array in which there will be looked for a specific address
*@param[in] "address address_to_find" The specific address that is looked for
*@return Returns the requested address
*/
int find_address_a(dyn_array_address *array, struct address address_to_find) {
  int res = 0;
  for (int i = 0; i < array->items; ++i) {
    if(strcmp(array->addresses[i].tags.house_number,address_to_find.tags.house_number)==0 && strcmp(array->addresses[i].tags.street,address_to_find.tags.street)==0) {
      res = 1;
    }
  }
  return res;
}