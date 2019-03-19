cmake_minimum_required(VERSION 3.13)
project(resource_monitor)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.56 REQUIRED COMPONENTS program_options)

add_executable(resource_monitor main.cpp)
target_include_directories(resource_monitor PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(resource_monitor Boost::program_options)