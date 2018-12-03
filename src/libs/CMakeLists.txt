add_library(convert_distance convert_distance_from_points.c)
install (TARGETS convert_distance DESTINATION bin)
install (FILES convert_fistance_from_points.h DESTINATION include)
