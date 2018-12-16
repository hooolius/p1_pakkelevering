cmake_minimum_required (VERSION 2.6)
project (p1_pakkelevering)
#Version number
set (p1_pakkelevering_VERSION_MAJOR 1)
set (p1_pakkelevering_VERSION_MINOR 1)

#configure the header file to pass CMake settings to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/main_config.h.in"
  "${PROJECT_BINARY_DIR}/main_config.h"
  )

#add the binary tree to the search path for include files
include_directories ("${PROJECT_BINARY_DIR}")

#include the map_gen lib
include_directories ("${PROJECT_SOURCE_DIR}/map_gen")
include_directories ("${PROJECT_SOURCE_DIR}/pathfinding")
include_directories ("${PROJECT_SOURCE_DIR}/combinatorial_optimisation")
include_directories ("${PROJECT_SOURCE_DIR}/libs")
add_subdirectory (pathfinding)
add_subdirectory (map_gen)
add_subdirectory (combinatorial_optimisation)
add_subdirectory (libs)

#include the dyn array lib

#add our executable
add_executable (p1_pakkelevering main.c)
target_link_libraries (p1_pakkelevering map_gen)
target_link_libraries (p1_pakkelevering combinatorial_optimisation)
target_link_libraries (p1_pakkelevering pathfinding)
target_link_libraries (p1_pakkelevering libs)
#include math.h
target_link_libraries(p1_pakkelevering m)

# add the install targets
install (TARGETS p1_pakkelevering DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/main_config.h"        
         DESTINATION include)
install(DIRECTORY app_data/ DESTINATION include/app_data)
