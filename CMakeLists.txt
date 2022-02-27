cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(Panda)

find_package(NTL REQUIRED)

add_compile_options(-Wall -Wextra -pedantic -Werror -std=c++11 -march=native)

add_subdirectory(src)