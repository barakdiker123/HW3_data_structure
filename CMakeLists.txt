
cmake_minimum_required(VERSION 3.5)

project(baz LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 3 REQUIRED)

add_executable(main main.cpp)
target_include_directories(main PUBLIC include)
target_link_libraries(main PRIVATE Catch2::Catch2WithMain)


add_executable(Queue src/Queue.cpp)
target_include_directories(Queue PUBLIC include)
target_link_libraries(Queue PRIVATE Catch2::Catch2WithMain)


add_executable(double_link src/double_linked_list.cpp)
target_include_directories(double_link PUBLIC include)
target_link_libraries(double_link PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(Queue)
catch_discover_tests(double_link)
