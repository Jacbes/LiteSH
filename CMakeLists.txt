cmake_minimum_required(VERSION 3.17)
project(LiteSH C)

set(CMAKE_C_STANDARD 99)

add_executable(LiteSH main.c)
target_link_libraries(LiteSH pthread)