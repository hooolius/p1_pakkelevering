cmake_minimum_required(VERSION 3.12)
project(map_and_parser C)

set(CMAKE_C_STANDARD 11)

add_executable(map_and_parser parser_addresses.c addresses_prompt.c main.c)