#include <stdio.h>

#define SOME_VALUE 10

struct a_point{
  float x;
  float y;
};

typedef struct a_point point;

int main(void) {
  a_star();
  return 0;
}

void a_star(point start, point goal) {
  point closed_list[SOME_VALUE];
  float start_g;
  float start_f = start_g + h;
  point open_list[SOME_VALUE] = start;
  point came_from[SOME_VALUE];
  point current;

  while (open_list != NULL) {
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

point reconstruct_path(came_from, current) {
  while (contains(came_from, current)) {
    insert(total_path);
  }
}

void insert(point list[], point point_to_insert) {

}

void delete(point list[], point point_to_delete) {

}

point extract_min(point list[]) {

}
