cmake_minimum_required(VERSION 3.13)
project(resource_monitor)
enable_testing()

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(vendor/Simple-Web-Server Simple-Web-Server)

find_package(Boost 1.56 REQUIRED COMPONENTS system thread filesystem program_options unit_test_framework)

add_executable(resource_monitor src/main.cpp)
target_include_directories(resource_monitor PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(resource_monitor ${Boost_LIBRARIES} simple-web-server)

file(GLOB TEST_SRC test/*.cpp)
add_executable(test_executable ${TEST_SRC})
target_include_directories(test_executable PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_executable ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME tests COMMAND test_executable)