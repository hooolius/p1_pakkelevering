/* dynamic_array.h - made with inspiration from book...*/

struct dyn_array {
  int low_water_mark;
  int high_water_mark;
  int min_capacity;
  int number_of_elements;
};

typedef dyn_array dyn_array;

void trim_to_size();

void ensure_capacity();

dyn_array resize_array(dyn_array *old_array, int new_size);

void add_element_to_end(dyn_array *array_to_insert_in, element element_to_insert);
