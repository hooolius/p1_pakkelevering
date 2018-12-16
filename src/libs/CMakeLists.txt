add_library(libs dynamic_array.c vincent_inv_dist_points.c cleaner.c cleaner.h)
install (TARGETS libs DESTINATION bin)
install (FILES dynamic_array.h vincent_inv_dist_points.h DESTINATION include)
