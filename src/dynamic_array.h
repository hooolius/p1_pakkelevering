/* dynamic_array.h - made with inspiration from
"A Practical Guide to Data Structures and Algorithms using Java" */

struct dyn_array {
  //The threshold for then the array is reduced in size
  int low_water_mark;
  //The threshold for then the array is expanded in size
  int high_water_mark;
  //The minimum size the array can have
  int min_capacity;
  //Number of items in array
  int items;
  //The size of the array
  //int size; maybe not needed
  element elements[];
};

typedef dyn_array dyn_array;

void trim_to_size();
/* Maybe implemented */
void ensure_capacity(dyn_array *array, int capacity);
/* Implemented */
dyn_array *resize_array(dyn_array *array, int new_size);
/* Implemented */
dyn_array *add_element_to_end(dyn_array *array_to_insert_in, element elem_to_insert);
/* Implemented */
dyn_array *delete_element(dyn_array *array, element elem_to_delete);
/* Not implemented yet */
void find_element();
