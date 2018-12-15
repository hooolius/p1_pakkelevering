add_library(pathfinding a_star.c convert_distance_from_points.c pairing_heap.c)
install (TARGETS pathfinding DESTINATION bin)
install (FILES a_star.h convert_distance_from_points.h pairing_heap.h DESTINATION include)
