/* dynamic_array.h - made with inspiration from
"A Practical Guide to Data Structures and Algorithms using Java" */

struct dyn_array {
  int low_water_mark;
  int high_water_mark;
  int min_capacity;
  int size;
};

typedef dyn_array dyn_array;

void trim_to_size();

void ensure_capacity();

dyn_array *resize_array(dyn_array *array, int new_size);

void add_element_to_end(dyn_array *array_to_insert_in, element element_to_insert);

void remove_range_of_elements();

void find_element();
