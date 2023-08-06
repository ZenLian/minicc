project(minicc)
cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
# add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
