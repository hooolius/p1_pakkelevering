add_library(map_gen STATIC address_to_point_calc.c map_parser.c parser_addresses.c addresses_prompt.c cJSON.c)
#install (TARGETS map_gen DESTINATION bin)
#install (FILES address_to_point_calc.h map_parser.h parser_addresses.h addresses_prompt.h cJSON.h DESTINATION include)
