add_library(libs dynamic_array.c vincent_inv_dist_points.c)
install (TARGETS libs DESTINATION bin)
install (FILES dynamic_array.h vincent_inv_dist_points.h DESTINATION include)
