cmake_minimum_required(VERSION 3.13)
project(resource_monitor)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(vendor/Simple-Web-Server Simple-Web-Server)

find_package(Boost 1.56 REQUIRED COMPONENTS system thread filesystem program_options)

add_executable(resource_monitor main.cpp)
target_include_directories(resource_monitor PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(resource_monitor ${Boost_LIBRARIES} simple-web-server)