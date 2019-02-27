cmake_minimum_required(VERSION 3.3.0)
project(a_tour_of_cpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wpedantic -Wall -Werror)

add_subdirectory(src)

