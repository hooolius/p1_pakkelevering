/* dynamic_array.h - made with inspiration from
"A Practical Guide to Data Structures and Algorithms using Java" */
#ifndef DYN_NODE2
#define DYN_NODE2

  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include "../pathfinding/pairing_heap.h"
  //#include "../pathfinding/a_star.h"
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
/* Makes a empty array */
dyn_array_heap *make_dyn_array_h(int size);

/* Not implemented yet */
void trim_to_size_h();

/* Maybe implemented */
void ensure_capacity_h(dyn_array_heap *array, int capacity);

/* Implemented */
dyn_array_heap *resize_array_h(dyn_array_heap *array, int new_size);

/* Implemented */
dyn_array_heap *add_heap_to_end_h(dyn_array_heap *array_to_insert_in, heap_node *heap_to_insert);
/* Implemented */
dyn_array_heap *delete_heap_h(dyn_array_heap *array, heap_node *heap_to_delete);

// NODE FUNCTIONS
dyn_array_node *make_dyn_array_n(int size);

/* Not implemented yet */
void trim_to_size_n();

/* Maybe implemented */
void ensure_capacity_n(dyn_array_node *array, int capacity);

/* Implemented */
dyn_array_node *resize_array_n(dyn_array_node *array, int new_size);

/* Implemented */
dyn_array_node *add_node_to_end_n(dyn_array_node *array_to_insert_in, node *node_to_insert);
/* Implemented */
dyn_array_node *delete_node_n(dyn_array_node *array, node *node_to_delete);

// ADDRESS FUNCTIONS
dyn_array_address *make_dyn_array_a(int min_capacity);

/* Not implemented yet */
void trim_to_size_a();

/* Maybe implemented */
void ensure_capacity_a(dyn_array_address *array, int capacity);

/* Implemented */
dyn_array_address *resize_array_a(dyn_array_address *array, int new_size);

/* Implemented */
dyn_array_address *add_address_to_end_a(dyn_array_address *array_to_insert_in, struct address address_to_insert);
/* Implemented */
dyn_array_address *delete_address_a(dyn_array_address *array, struct address *address_to_delete);
/* Not implemented yet */
int find_address_a(dyn_array_address *array, struct address address_to_find);

// INTEGER FUNCTIONS
dyn_array_int *make_dyn_array_i(int min_capacity);

/* Not implemented yet */
void trim_to_size_a();

/* Maybe implemented */
void ensure_capacity_i(dyn_array_int *array, int capacity);

/* Implemented */
dyn_array_int *resize_array_i(dyn_array_int *array, int new_size);

/* Implemented */
dyn_array_int *add_int_to_end_i(dyn_array_int *array_to_insert_in, int int_to_insert);
/* Implemented */
dyn_array_int *delete_int_i(dyn_array_int *array, int int_to_delete);
