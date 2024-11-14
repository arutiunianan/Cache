cmake_minimum_required(VERSION 3.10)

project(my_cache)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if(NO_OPTIMIZATION)
    target_compile_definitions(lfu PRIVATE NO_OPTIMIZATION=1)
    target_compile_definitions(pca PRIVATE NO_OPTIMIZATION=1)
endif()

if(TEST)
    add_definitions(-DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
    find_package(GTest REQUIRED)

    add_executable(test test/test.cpp)
    target_include_directories(test PRIVATE ${GTEST_INCLUDE_DIRS})
    target_link_libraries(test GTest::GTest GTest::Main)
else()
    add_executable(lfu lfu.cpp graph/graph.cpp)
    target_include_directories(lfu PRIVATE cache graph)

    add_executable(pca pca.cpp graph/graph.cpp)
    target_include_directories(pca PRIVATE cache graph)
endif()

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Enabling AddressSanitizer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
endif()