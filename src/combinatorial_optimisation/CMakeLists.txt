add_library(combinatorial_optimisation held_karp.c ioconverter.c greedy.c)
install (TARGETS combinatorial_optimisation DESTINATION bin)
install (FILES held_karp.h ioconverter.h greedy.h DESTINATION include)