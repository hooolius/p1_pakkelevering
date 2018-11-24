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

  while (open_list != 0) {
    current = extract_min(open_list);
    if(current.x == goal.x && current.y == goal.y){
      return reconstruct_path(came_from, current);
    }
    delete(open_list, current);
    insert(closed_list, current);
    int number_of_neighbours = calculate_neighbours();
    for (size_t i = 0; i < ; i++) {
      if (contains(closed_list, neighbour)) {
        continue;
      }

    }
  }
}

point reconstruct_path(came_from, current) {
  while (contains(came_from, current)) {
    insert(total_path);
  }
}

void insert(point list, point point_to_insert) {

}

point extract_min(point list[]) {

}
