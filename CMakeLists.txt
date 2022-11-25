
cmake_minimum_required(VERSION 3.5)

project(baz LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)

#find_package(Catch2 3 REQUIRED)
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

#add_executable(main main.cpp)
#target_include_directories(main PUBLIC include)
#target_link_libraries(main PRIVATE Catch2::Catch2WithMain)


add_executable(Queue src/Queue.cpp)
target_include_directories(Queue PUBLIC include)
target_link_libraries(Queue PRIVATE Catch2::Catch2WithMain)


add_executable(double_link src/double_linked_list.cpp)
target_include_directories(double_link PUBLIC include)
target_link_libraries(double_link PRIVATE Catch2::Catch2WithMain)


add_executable(tree_question1 src/tree_question1.cpp)
target_include_directories(tree_question1 PUBLIC include)
target_link_libraries(tree_question1 PRIVATE Catch2::Catch2WithMain)

add_executable(handshake src/hand_shake_project.cpp)
target_include_directories(handshake PUBLIC include)
target_link_libraries(handshake PRIVATE Catch2::Catch2WithMain)

add_executable(question2 src/question2.cpp)
target_include_directories(question2 PUBLIC include)
target_link_libraries(question2 PRIVATE Catch2::Catch2WithMain)

add_executable(question3a src/question3a.cpp)
target_include_directories(question3a PUBLIC include)
target_link_libraries(question3a PRIVATE Catch2::Catch2WithMain)

add_executable(question3b src/question3b.cpp)
target_include_directories(question3b PUBLIC include)
target_link_libraries(question3b PRIVATE Catch2::Catch2WithMain)

add_executable(question4 src/question4.cpp)
target_include_directories(question4 PUBLIC include)
target_link_libraries(question4 PRIVATE Catch2::Catch2WithMain)

add_executable(question6b src/question6b.cpp)
target_include_directories(question6b PUBLIC include)
target_link_libraries(question6b PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(Queue)
catch_discover_tests(double_link)
catch_discover_tests(tree_question1)
catch_discover_tests(handshake)
catch_discover_tests(question2)
catch_discover_tests(question3a)
catch_discover_tests(question3b)
catch_discover_tests(question4)
catch_discover_tests(question6b)
