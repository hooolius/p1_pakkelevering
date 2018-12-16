#include "dynamic_array.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

dyn_array_heap *resize_array_h(dyn_array_heap *array, int new_size);

/* HEAP FUNCTIONS */
/**
*@brief This function initializes the dyn_array_node
*@param[in] min_capacity This parameter decides the inital size of the dynamic array
*@return Returns a pointer to the dynamic array
*/
dyn_array_heap *make_dyn_array_h(int min_capacity) {
  dyn_array_heap *array = calloc(1, sizeof(dyn_array_heap));
  array->heap_nodes = calloc(min_capacity, sizeof(heap_node*) * 2 * min_capacity);
  array->min_capacity = min_capacity;
  array->low_water_mark = min_capacity;
  array->high_water_mark = 2 * min_capacity;
  array->items = 0;
  return array;
}

/**
*@brief This function resizes the dynamic array
*@param[in] "dyn_array_heap *array" The dynamic array that needs resizing
*@param[in] new_size The number of possible elements in the array
*@return Returns a pointer to the dynamic array
*/
dyn_array_heap *resize_array_h(dyn_array_heap *array, int new_size) {
  array->low_water_mark = (int)ceil(new_size/4);
  array->high_water_mark = new_size;
  array->heap_nodes = realloc(array->heap_nodes, new_size * sizeof(heap_node));
  if(array->heap_nodes == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

/**
*@brief This function adds another element to the end of an array
*@param[in] "dyn_array_heap* array_to_insert_in"  is the array in which a new element has to be added
*@param[in] "heap_node heap_to_insert" The data that has to be inserted into the array
*@return Returns a pointer to the resized array
*/
dyn_array_heap *add_heap_to_end_h(dyn_array_heap *array_to_insert_in, heap_node *heap_to_insert) {
  dyn_array_heap *res = array_to_insert_in;
  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    res = resize_array_h(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->heap_nodes[array_to_insert_in->items] = heap_to_insert;
  ++array_to_insert_in->items;
  /* If array is not resized then NULL is returned */
  return res;
}

void ensure_capacity_h(dyn_array_heap *array, int capacity) {
    array->min_capacity = capacity;
}

/**
*@brief This function deletes a node in the dynamic array
*@param[in] "dyn_array_heap *array" The array in which a node has to be deleted
*@param[in] "heap_node *heap_to_delete" is the node that will be deleted
*@return Returns a pointer to the resized array
*/
dyn_array_heap *delete_heap_h(dyn_array_heap *array, heap_node *heap_to_delete) {
  dyn_array_heap *res = array;
  for (int i = 0; i < array->items; ++i) {
    if(array->heap_nodes[i]->element == heap_to_delete->element) {
      if(i == 0) {
 //       array->heap_nodes[i] = memset(array->heap_nodes[i], 0 , sizeof(heap_node*));//array->heap_nodes[array->items-1];
      }
      else {
        array->heap_nodes[i] = array->heap_nodes[array->items-1];
      }
      --array->items;
    }
  }
  if(array->items < array->low_water_mark) {
    res = resize_array_h(res, MAX((int)ceil(array->high_water_mark/4), array->min_capacity));
  }
  return res;
}

/**
*@brief This function finds a specific node
*@param[in] "dyn_array_heap *array" The array in which there will be looked for a specific node
*@param[in] "heap_node heap_to_find" The speciic node that is looked for
*@return Returns a pointer to the resized array
*/
dyn_array_heap *find_heap_h(dyn_array_heap *array, heap_node heap_to_find) {
  dyn_array_heap *res;
  for (int i = 0; i < array->items; ++i) {
    if (array->heap_nodes[i]->element == heap_to_find.element) {
      res = &array->heap_nodes[i];
    }
    return res;
  }
}

/* NODE FUNCTIONS */
/**
*@brief This function initializes the dyn_array_node
*@param[in] min_capacity This parameter decides the inital size of the dynamic array
*@return Returns a pointer to the dynamic array
*/
dyn_array_node *make_dyn_array_n(int min_capacity) {
  dyn_array_node *array = calloc(1, sizeof(dyn_array_node));
  array->nodes = (node**)calloc(min_capacity, sizeof(node*) * 2 * min_capacity);
  array->min_capacity = min_capacity;
  array->low_water_mark = min_capacity;
  array->high_water_mark = 2 * min_capacity;
  array->items = 0;
  return array;
}

/**
*@brief This function resizes the dynamic array
*@param[in] "dyn_array_node *array" The dynamic array that needs resizing
*@param[in] new_size The number of possible elements in the array
*@return Returns a pointer to the dynamic array
*/
dyn_array_node *resize_array_n(dyn_array_node *array, int new_size) {
  array->low_water_mark = (int)ceil(new_size/4);
  array->high_water_mark = new_size;
  array->nodes = realloc(array->nodes, new_size * sizeof(node*));
  if(array->nodes == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}


/**
*@brief This function adds another element to the end of an array
*@param[in] "dyn_array_node *array_to_insert_in" is the array in which a new element has to be added
*@param[in] "node node_to_insert" The data that has to be inserted into the array
*@return Returns a pointer to the resized array
*/
dyn_array_node *add_node_to_end_n(dyn_array_node *array_to_insert_in, node *node_to_insert) {

  dyn_array_node *res = array_to_insert_in;

  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    res = resize_array_n(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->nodes[array_to_insert_in->items] = node_to_insert;
  array_to_insert_in->items += 1;
  /* If array is not resized then NULL is returned */
  return res;
}

void ensure_capacity_n(dyn_array_node *array, int capacity) {
  array->min_capacity = capacity;
}

/**
*@brief This function deletes a node in the dynamic array
*@param[in] "dyn_array_node *array" The array in which a node has to be deleted
*@param[in] "node *node_to_delete" is the node that will be deleted
*@return Returns a pointer to the resized array
*/
dyn_array_node *delete_node_n(dyn_array_node *array, node *node_to_delete) {
  dyn_array_node *res = array;
  for (int i = 0; i < array->items; ++i) {
    if(array->nodes[i]->id == node_to_delete->id) {
      array->nodes[i] = array->nodes[array->items - 1];
      array->items -= 1;
    }
  }
  if(array->items < array->low_water_mark) {
    res = resize_array_n(res, MAX((int)ceil(array->high_water_mark/4), array->min_capacity));
  }
  return res;
}

/**
*@brief This function finds a specific node
*@param[in] "dyn_array_node *array" The array in which there will be looked for a specific node
*@param[in] "node node_to_find" The speciic node that is looked for
*@return Returns a pointer to the resized array
*/
dyn_array_node *find_node_n(dyn_array_node *array, node node_to_find) {
  dyn_array_node *res;
  for (int i = 0; i < array->items; ++i) {
    if(array->nodes[i]->id == node_to_find.id) {
      res = array->nodes[i];
    }
  }
  return res;
}

/* Addresses Functions */
/**
*@brief This function makes a dynamic array for addresses
*@param[in] min_capacity This parameter decides the inital size of the dynamic array
*@return Returns a pointer to the resized array
*/
dyn_array_address *make_dyn_array_a(int min_capacity) {
  dyn_array_address *array = calloc(1, sizeof(dyn_array_address));
  array->addresses = calloc(min_capacity, sizeof(struct address) * 2 * min_capacity);
  array->min_capacity = min_capacity;
  array->low_water_mark = min_capacity;
  array->high_water_mark = 2 * min_capacity;
  array->items = 0;
  return array;
}

/**
*@brief This function resizes the dynamic array
*@param[in] "dyn_array_address *array" The dynamic array that needs resizing
*@param[in] new_size The number of possible elements in the array
*@return Returns a pointer to the dynamic array
*/
dyn_array_address *resize_array_a(dyn_array_address *array, int new_size) {
  array->low_water_mark = (int)ceil(new_size/4);
  array->high_water_mark = new_size;
  array->addresses = realloc(array->addresses, new_size * sizeof(struct address));
  if(array->addresses == NULL) {
    exit(EXIT_FAILURE);
  }
  return array;
}

/**
*@brief This function adds another element to the end of an array
*@param[in] "dyn_array_address *array_to_insert_in"  is the array in which a new element has to be added
*@param[in] "address address_to_insert" The data that has to be inserted into the array
*@return Returns a pointer to the resized array
*/
dyn_array_address *add_address_to_end_a(dyn_array_address *array_to_insert_in, struct address address_to_insert) {
  dyn_array_address *res = array_to_insert_in;

  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    res = resize_array_a(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->addresses[array_to_insert_in->items] = address_to_insert;
  array_to_insert_in->items += 1;
  /* If array is not resized then NULL is returned */
  return res;
}

void ensure_capacity_a(dyn_array_address *array, int capacity) {
  array->min_capacity = capacity;
}

/**
*@brief This function deletes a node in the dynamic array
*@param[in] "dyn_array_address *array" The array in which a node has to be deleted
*@param[in] "address *address_to_delete" The node that will be deleted
*@return Returns a pointer to the resized array
*/
dyn_array_address *delete_address_a(dyn_array_address *array, struct address *address_to_delete) {
  dyn_array_address *res = array;
  for (int i = 0; i < array->items; ++i) {
    if(array->addresses[i].id == address_to_delete->id) {
      array->addresses[i] = array->addresses[array->items - 1];
      array->items -= 1;
    }
  }
  if(array->items < array->low_water_mark) {
    res = resize_array_a(res, MAX((int)ceil(array->high_water_mark/4), array->min_capacity));
  }
  return res;
}

/**
*@brief This function finds a specific node
*@param[in] "dyn_array_address *array" The array in which there will be looked for a specific node
*@param[in] "address address_to_find" The speciic node that is looked for
*@return Returns a pointer to the resized array
*/
dyn_array_address *find_address_a(dyn_array_address *array, struct address address_to_find) {
  dyn_array_address *res;
  for (int i = 0; i < array->items; ++i) {
    if(array->addresses[i].id == address_to_find.id) {
      res = &array->addresses[i];
    }
  }
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

  /* If array is not able to hold another element then resize array */
  if(array_to_insert_in->items >= array_to_insert_in->high_water_mark) {
    /* If array is resized then a pointer to the new array is returned */
    res = resize_array_i(array_to_insert_in, 2 * array_to_insert_in->high_water_mark);
  }
  array_to_insert_in->integers[array_to_insert_in->items] = int_to_insert;
  array_to_insert_in->items += 1;
  /* If array is not resized then NULL is returned */
  return res;
}

void ensure_capacity_i(dyn_array_int *array, int capacity) {
  array->min_capacity = capacity;
}

dyn_array_int *delete_int_i(dyn_array_int *array, int int_to_delete) {
  dyn_array_int *res = array;
  for (int i = 0; i < array->items; ++i) {
    if(array->integers[i] == int_to_delete) {
      array->integers[i] = array->integers[array->items - 1];
      array->items -= 1;
    }
  }
  if(array->items < array->low_water_mark) {
    res = resize_array_i(res, MAX((int)ceil(array->high_water_mark/4), array->min_capacity));
  }
  return res;
}

dyn_array_int *find_int_i(dyn_array_int *array, int int_to_find) {
  dyn_array_int *res;
  for (int i = 0; i < array->items; ++i) {
    if(array->integers[i] == int_to_find) {
      res = &array->integers[i];
    }
  }
  return res;
}
