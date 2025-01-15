cmake_minimum_required(VERSION 3.21)
project(Allocators)

set(CMAKE_CXX_STANDARD 20)

add_executable(allocator main.cpp allocator.cpp)

target_compile_options(allocator PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(allocator PRIVATE -fsanitize=address)