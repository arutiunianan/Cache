cmake_minimum_required(VERSION 3.10)

project(my_cache)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(lfu lfu.cpp)
add_executable(pca pca.cpp)
add_executable(both main.cpp graph/graph.cpp)
target_include_directories(lfu PRIVATE cache)
target_include_directories(pca PRIVATE cache)
target_include_directories(both PRIVATE cache graph)

if(NO_OPTIMIZATION)
    target_compile_definitions(lfu PRIVATE NO_OPTIMIZATION=1)
    target_compile_definitions(pca PRIVATE NO_OPTIMIZATION=1)
    target_compile_definitions(both PRIVATE NO_OPTIMIZATION=1)
endif()

if(TEST)
    target_compile_definitions(lfu PRIVATE TEST=1)
    target_compile_definitions(pca PRIVATE TEST=1)
    target_compile_definitions(both PRIVATE TEST=1)
endif()

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Enabling AddressSanitizer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
endif()