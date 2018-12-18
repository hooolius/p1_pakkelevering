/* dynamic_array.h - made with inspiration from
"A Practical Guide to Data Structures and Algorithms using Java" */
#ifndef DYN_NODE2
#define DYN_NODE2
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include "../pathfinding/pairing_heap.h"
#endif

#ifndef DYN_NODE
#define DYN_NODE
  typedef struct dyn_array_node dyn_array_node;
  struct dyn_array_node {
    int low_water_mark;
    int high_water_mark;
    int min_capacity;
    int number_of_elements;
    int items;
    node **nodes;
  };
#endif

  #include "../map_gen/parser_addresses.h"

#ifndef DYN_ADDRESS
#define DYN_ADDRESS
    struct dyn_array_address {
      int low_water_mark;
      int high_water_mark;
      int min_capacity;
      int number_of_elements;
      int items;
      struct address *addresses;
    };
    typedef struct dyn_array_address dyn_array_address;
#endif

#ifndef DYN_INT
#define DYN_INT
    typedef struct dyn_array_int dyn_array_int;

    struct dyn_array_int {
      int low_water_mark;
      int high_water_mark;
      int min_capacity;
      int number_of_elements;
      int items;
      int *integers;
    };
#endif

/* HEAP FUNCTIONS */
/**
*@brief This function initializes the dyn_array_heap
*@param[in] min_capacity This parameter decides the initial size of the dynamic array
*@return Returns a pointer to the dynamic array
*/
dyn_array_heap *make_dyn_array_h(int size);
/**
*@brief This function resizes the dynamic array
*@param[in] "dyn_array_heap *array" The dynamic array that needs resizing
*@param[in] new_size The number of possible elements in the array
*@return Returns a pointer to the dynamic array
*/
dyn_array_heap *resize_array_h(dyn_array_heap *array, int new_size);
/**
*@brief This function adds another element to the end of an array
*@param[in] "dyn_array_heap* array_to_insert_in"  is the array in which a new element has to be added
*@param[in] "heap_node heap_to_insert" The data that has to be inserted into the array
*@return Returns a pointer to the array
*/
dyn_array_heap *add_heap_to_end_h(dyn_array_heap *array_to_insert_in, heap_node *heap_to_insert);

// NODE FUNCTIONS
/**
*@brief This function initializes the dyn_array_node
*@param[in] min_capacity This parameter decides the initial size of the dynamic array
*@return Returns a pointer to the dynamic array
*/
dyn_array_node *make_dyn_array_n(int size);
/**
*@brief This function resizes the dynamic array
*@param[in] "dyn_array_node *array" The dynamic array that needs resizing
*@param[in] new_size The number of possible elements in the array
*@return Returns a pointer to the dynamic array
*/
dyn_array_node *resize_array_n(dyn_array_node *array, int new_size);
/**
*@brief This function adds another element to the end of a dyn array
*@param[in] "dyn_array_node *array_to_insert_in" is the array in which a new element has to be added
*@param[in] "node node_to_insert" The data that has to be inserted into the array
*@return Returns a pointer to the dyn array
*/
dyn_array_node *add_node_to_end_n(dyn_array_node *array_to_insert_in, node *node_to_insert);

// ADDRESS FUNCTIONS
/**
*@brief This function makes a dynamic array for addresses
*@param[in] min_capacity This parameter decides the initial size of the dynamic array
*@return Returns a pointer to the dynamic array
*/
dyn_array_address *make_dyn_array_a(int min_capacity);
/**
*@brief This function resizes the dynamic array
*@param[in] "dyn_array_address *array" The dynamic array that needs resizing
*@param[in] new_size The number of possible elements in the array
*@return Returns a pointer to the dynamic array
*/
dyn_array_address *resize_array_a(dyn_array_address *array, int new_size);
/**
*@brief This function adds another element to the end of an array
*@param[in] "dyn_array_address *array_to_insert_in"  is the array in which a new element has to be added
*@param[in] "address address_to_insert" The data that has to be inserted into the array
*@return Returns a pointer to the dynamic array
*/
dyn_array_address *add_address_to_end_a(dyn_array_address *array_to_insert_in, struct address address_to_insert);

int find_address_a(dyn_array_address *array, struct address address_to_find);

// INTEGER FUNCTIONS
/**
*@brief This function makes a dynamic array for integers
*@param[in] min_capacity This parameter decides the initial size of the dynamic array
*@return Returns a pointer to the dynamic array
*/
dyn_array_int *make_dyn_array_i(int min_capacity);
/**
*@brief This function resizes the dynamic array
*@param[in] "dyn_array_int *array" The dynamic array that needs resizing
*@param[in] new_size The number of possible integers in the array
*@return Returns a pointer to the dynamic array
*/
dyn_array_int *resize_array_i(dyn_array_int *array, int new_size);
/**
*@brief This function adds another integer to the end of an array
*@param[in] "dyn_array_int *array_to_insert_in"  is the array in which a new integer has to be added
*@param[in] "int int_to_insert" The integer that has to be inserted into the array
*@return Returns a pointer to the dynamic array
*/
dyn_array_int *add_int_to_end_i(dyn_array_int *array_to_insert_in, int int_to_insert);
