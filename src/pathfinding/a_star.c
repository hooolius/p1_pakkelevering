#include "a_star.h"

node *convert_points_to_nodes(int number_of_points, point *points);

node *convert_point_to_node(point *the_point);

int count_elements_in_list(dyn_array_node *list);

/* Function copys one node to a other node */
void copy_node_to_node(node *destination, node *source);

node *find_min_array(dyn_array_node *list);

node *reconstruct_path(dyn_array_node *came_from);

dyn_array_node *make_neighbours_list(node current, node *nodes);

int contains(dyn_array_node *closed_list, node item);

int cmp_func(const void *a, const void *b);


/* A star setup */
node *a_star(point *start_p, point *goal_p, point *points) {
    int number_of_points = 0;
    while (points[number_of_points].id != 0) {
        ++number_of_points;
    }

    /* Debug code */
    node *start = convert_point_to_node(start_p);
    node *goal = convert_point_to_node(goal_p);
    node *nodes = convert_points_to_nodes(number_of_points, points);

    /*for (int j = 0; j < number_of_points; ++j) {
      printf("ID:%.0lf LAT: %.0lf LON: %.0lf\n", nodes[j].id, nodes[j].lat, nodes[j].lon);
    }*/

    int count = 0;
    dyn_array_node *closed_list = make_dyn_array_n(100);
    start->g = 0;
    start->f = start->g + vincent_inv_dist(start->lat, start->lon, goal->lat, goal->lon);
    //pairing_heap open_list;
    dyn_array_node *open_list = make_dyn_array_n(10);
    //heap_clear(open_list);
    add_node_to_end_n(open_list, *start);
    dyn_array_node *came_from = make_dyn_array_n(100);
    node *current;
    node neighbour;

    //heap_insert(open_list, start);
    //heap_insert(open_list, start);
    /* A star algoritme */
    while (count_elements_in_list(open_list) != 0) {
        /* Take node with the smallest value and copy to current */
        copy_node_to_node(current, find_min_array(open_list));
        /* if the distance to goal is less than 1 meter then reconstruct path */
        if (vincent_inv_dist(current->lat, current->lon, goal->lat, goal->lon) < 1.0) {
            free(closed_list);
            free(open_list);
            return reconstruct_path(came_from);
        }
        /* Move current node from open_list to closed_list */
        //heap_delete(open_list, current);
        delete_node_n(open_list, current);
        add_node_to_end_n(closed_list, *current);
        /* Count number of neighbours and check if they exied in closed_list */
        dyn_array_node *neighbour_list = make_neighbours_list(*current, nodes);
        for (size_t i = 0; i < neighbour_list->items; ++i) {
            if (contains(closed_list, neighbour_list->nodes[i])) {
                continue;   // husk at ændre neighbour til neighbour[i] i koden
            }
            /* Neighbour is calculated and put in open_list and current is put in came_from */
            neighbour_list->nodes[i].g = current->g +
                                         vincent_inv_dist(current->lat, current->lon, neighbour_list->nodes[i].lat,
                                                          neighbour_list->nodes[i].lon);
            neighbour_list->nodes[i].h = vincent_inv_dist(neighbour_list->nodes[i].lat, neighbour_list->nodes[i].lon,
                                                          goal->lat, goal->lon);
            neighbour_list->nodes[i].f = neighbour_list->nodes[i].h + neighbour_list->nodes[i].g;
            //heap_insert(open_list, neighbour_list.nodes[i]);
            add_node_to_end_n(open_list, neighbour_list->nodes[i]);
            add_node_to_end_n(came_from, *current);
            ++count;
        }
        free(neighbour_list);
    }
    printf("A star: No path exiting program!\n");
    exit(-1);
}

node *find_min_array(dyn_array_node *list) {
    //qsort(list->nodes, list->items, sizeof(node), cmp_func);
    return &list->nodes[0];
}

int cmp_func(const void *a, const void *b) {
    int res;
    node *aa = (node *) a;
    node *bb = (node *) b;

    if (aa->f > bb->f) {
        res = -1;
    }
    else if (aa->f == aa->f) {
        res = 0;
    }
    else {
        res = 1;
    }
    return res;
}

dyn_array_node *make_neighbours_list(node current, node *nodes) {
    /* Follow pointers and count number of neighbours */
    /* return a pointer from a memory space where neighbours are stored */
    dyn_array_node *neighbour_list = make_dyn_array_n(6);
    if (current.p1 != 0) {
        neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p1 - 0]);
    }
    if (current.p2 != 0) {
        neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p2 - 0]);
    }
    if (current.p3 != 0) {
        neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p3 - 0]);
    }
    if (current.p4 != 0) {
        neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p4 - 0]);
    }
    if (current.p5 != 0) {
        neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p5 - 0]);
    }
    if (current.p6 != 0) {
        neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p6 - 0]);
    }
    return neighbour_list;
}

/* Function copys one node to a other node */
void copy_node_to_node(node *destination, node *source) {
  destination->id = source->id;
  destination->lat = source->lat;
  destination->lon = source->lon;
  destination->is_active = source ->is_active;
  destination->g = source->g;
  destination->h = source->h;
  destination->f = source->f;
  destination->p1 = source->p1;
  destination->p2 = source->p2;
  destination->p3 = source->p3;
  destination->p4 = source->p4;
  destination->p5 = source->p5;
  destination->p6 = source->p6;
}

int count_elements_in_list(dyn_array_node *list) {
    return list->items;
}

int contains(dyn_array_node *closed_list, node item) {
    int res = 0;
    for (int i = 0; i < closed_list->items; ++i) {
        if (closed_list->nodes[i].id == item.id) {
            res = 1;
            break;
        }
    }
    return res;
}

node *reconstruct_path(dyn_array_node *came_from) {
    node *total_path = calloc(came_from->items, sizeof(node));
    for (int i = 0; i < came_from->items; i++) {
        total_path[i] = came_from->nodes[i];
    }
    free(came_from);
    return total_path;
}

node *convert_points_to_nodes(int number_of_points, point *points) {
    node *nodes = calloc(number_of_points, sizeof(struct node));
    for (int i = 0; i < number_of_points; ++i) {
        nodes[i].id = points[i].id;
        nodes[i].lon = points[i].lon;
        nodes[i].lat = points[i].lat;
        nodes[i].is_active = 0;
        nodes[i].g = 0;
        nodes[i].h = 0;
        nodes[i].f = 0;
        nodes[i].p1 = points[i].p1;
        nodes[i].p2 = points[i].p2;
        nodes[i].p3 = points[i].p3;
        nodes[i].p4 = points[i].p4;
        nodes[i].p5 = points[i].p5;
        nodes[i].p6 = points[i].p6;
    }
    return nodes;
}

node *convert_point_to_node(point *point) {
    node *node = calloc(1, sizeof(struct node));
    node->id = point->id;
    node->lon = point->lon;
    node->lat = point->lat;
    node->is_active = 0;
    node->g = 0;
    node->h = 0;
    node->f = 0;
    node->p1 = point->p1;
    node->p2 = point->p2;
    node->p3 = point->p3;
    node->p4 = point->p4;
    node->p5 = point->p5;
    node->p6 = point->p6;
    return node;
}
