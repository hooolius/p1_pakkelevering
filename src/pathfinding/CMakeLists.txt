add_library(pathfinding a_star.c pairing_heap.c)
install (TARGETS pathfinding DESTINATION bin)
install (FILES a_star.h pairing_heap.h DESTINATION include)
