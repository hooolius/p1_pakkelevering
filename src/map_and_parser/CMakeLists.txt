cmake_minimum_required(VERSION 3.12)
project(map_and_parser C)

set(CMAKE_C_STANDARD 11)

add_executable(map_and_parser map_parser.c map_parser.h parser_addresses.h parser_addresses.c address_to_point_calc.c main.c addresses_prompt.c addresses_prompt.h address_to_point_calc.h)