#include <stdio.h>

#define SOME_VALUE 10

struct a_node{
  float lat;
  float lon;
  double g;
  double h;
  double f;
};

typedef struct a_node node;

int main(void) {
  a_star();
  return 0;
}

void a_star(node start, node goal) {
  node closed_list[SOME_VALUE];
  float start_g;
  float start_f = start_g + h;
  node open_list[SOME_VALUE] = start;
  node came_from[SOME_VALUE];
  node current;

  node neighbour;

  insert(open_list, start);
  /* A star algoritme  */
  while (count_elements_in_list(open_list) != 0) {
    /* Take node with the smallest value and copy to current */
    copy_node_to_node(current, extract_min(open_list));
    /* if the distance to goal is less than 1 meter then reconstruct path */
    if(jorden_er_ikke_flad(current, goal) < 1){
      return reconstruct_path(came_from, current);
    }
    /* Move current node from open_list to closed_list */
    delete(open_list, current);
    insert(closed_list, current);
    /* Count number of neighbours and check if they exied in closed_list */
    int number_of_neighbours = calculate_neighbours();
    for (size_t i = 0; i < number_of_neighbours; ++i) {
      if (contains(closed_list, neighbour)) {
        continue;
      }
    /* Neighbour is calculated and put in open_list and current is put in came_from */
    neighbour.g = current_g + jorden_er_ikke_flad(current, neighbour);
    neighbour.h = jorden_er_ikke_flad(neighbour, goal);
    neighbour.f = neighbour_h + neighbour_g;
    insert(open_list, neighbour);
    insert(came_from, current);
    }
  }
}

void copy_node_to_node(node destination, node source){
  destination.lat = source.lat;
  destination.lon = source.lon;
}

int count_elements_in_list(node *list){
  int res = 0;
  for (size_t i = 0; i < count; i++) {
    if (list[i].x != 0 && list[i].y != 0) {
      ++res;
    }
  }
  return res;
}

node reconstruct_path(came_from, current) {
  while (contains(came_from, current)) {
    insert(total_path, current);
    current = came_from[current];
  }
}

void insert(node list[], node node_to_insert) {

}

void delete(node list[], node node_to_delete) {

}

node extract_min(node list[]) {

}

/*
#include <stdio.h>

#define SOME_VALUE 10

struct a_node{
  float x;
  float y;
};

typedef struct a_node node;

int main(void) {
  a_star();
  return 0;
}

void a_star(node start, node goal) {
  node closed_list[SOME_VALUE];
  float start_g;
  float start_f = start_g + h;
  node open_list[SOME_VALUE] = start;
  node came_from[SOME_VALUE];
  node current;

  while (count_elements_in_list(open_list) != 0) {
    current = extract_min(open_list);
    if(current.x == goal.x && current.y == goal.y){
      return reconstruct_path(came_from, current);
    }
    delete(open_list, current);
    insert(closed_list, current);
    int number_of_neighbours = calculate_neighbours();
    for (size_t i = 0; i < number_of_neighbours; ++i) {
      if (contains(closed_list, neighbour)) {
        continue;
      }
    neighbour_g = current_g + jorden_er_ikke_flad(current, neighbour);
    neighbour_h = jorden_er_ikke_flad(neighbour, goal);
    neighbour_f = neighbour_h + neighbour_g;
    insert(open_list, neighbour);
    came_from[i] = current;
    }
  }
}

void copy_node_to_node(node destination, node source){
  destination.x = source.x;
  destination.y = source.y;
}

int count_elements_in_list(node *list){
  int res = 0;
  for (size_t i = 0; i < count; i++) {
    if (list[i].x != 0 && list[i].y != 0) {
      ++res;
    }
  }
  return res;
}

node reconstruct_path(came_from, current) {
  while (contains(came_from, current)) {
    insert(total_path);
  }
}

void insert(node list[], node node_to_insert) {

}

void delete(node list[], node node_to_delete) {

}

node extract_min(node list[]) {

}

*/
