cmake_minimum_required(VERSION 3.10)

project(my_cache)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(cache main.cpp graph/graph.cpp)
target_include_directories(cache PRIVATE cache graph)

if(NO_OPTIMIZATION)
    target_compile_definitions(cache PRIVATE NO_OPTIMIZATION=1)
endif()

add_definitions(-DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
find_package(GTest REQUIRED)
if(TEST)
    add_executable(test test/test.cpp)
    target_include_directories(test PRIVATE ${GTEST_INCLUDE_DIRS})
    target_link_libraries(test GTest::GTest GTest::Main)
endif()

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(cache ${Boost_LIBRARIES})

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Enabling AddressSanitizer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
endif()