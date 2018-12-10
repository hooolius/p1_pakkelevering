cmake_minimum_required (VERSION 2.6)
project (p1_pakkelevering)
#Version number
set (p1_pakkelevering_VERSION_MAJOR 0)
set (p1_pakkelevering_VERSION_MINOR 4)

#configure the header file to pass CMake settings to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/main_config.h.in"
  "${PROJECT_BINARY_DIR}/main_config.h"
  )

#add the binary tree to the search path for include files
include_directories ("${PROJECT_BINARY_DIR}")

#include the distance lib
include_directories ("${PROJECT_SOURCE_DIR}/map_gen")
add_subdirectory (map_gen)

#add our executable
add_executable (p1_pakkelevering main.c)
target_link_libraries (p1_pakkelevering map_gen)

# add the install targets
install (TARGETS p1_pakkelevering DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/main_config.h"        
         DESTINATION include)
install(DIRECTORY app_data/ DESTINATION include/app_data)
