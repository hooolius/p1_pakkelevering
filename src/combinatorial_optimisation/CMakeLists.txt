add_library(combinatorial_optimisation held_karp.c ioconverter.c)
install (TARGETS combinatorial_optimisation DESTINATION bin)
install (FILES held_karp.h ioconverter.h DESTINATION include)