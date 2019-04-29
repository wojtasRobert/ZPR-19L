cmake_minimum_required(VERSION 3.13)
project(resmond)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (MSVC)
	link_directories(C:/local/boost_1_69_0/lib64-msvc-14.1)
endif ()

add_subdirectory(vendor/Simple-Web-Server Simple-Web-Server)

find_package(Boost 1.56 REQUIRED COMPONENTS program_options unit_test_framework)

file(GLOB MAIN_SRC src/resmond/*.cpp include/resmond/*.hpp)
add_executable(resmond ${MAIN_SRC} src/main.cpp)
target_include_directories(resmond PRIVATE ${Boost_INCLUDE_DIRS} vendor/Simple-Web-Server include)
if (MSVC)
	target_link_libraries(resmond simple-web-server)
else ()
	target_link_libraries(resmond Boost::program_options simple-web-server)
endif ()

file(GLOB TEST_SRC test/*.cpp)
add_executable(test_executable ${TEST_SRC} ${MAIN_SRC})
target_include_directories(test_executable PRIVATE ${Boost_INCLUDE_DIRS} vendor/Simple-Web-Server include)
target_compile_definitions(test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_executable Boost::unit_test_framework simple-web-server)
add_test(NAME tests COMMAND test_executable)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    set(COVERAGE_GCOVR_EXCLUDES ${PROJECT_SOURCE_DIR}/vendor ${PROJECT_SOURCE_DIR}/test)
    SETUP_TARGET_FOR_COVERAGE_GCOVR_HTML(NAME ctest_coverage EXECUTABLE test_executable DEPENDENCIES test_executable)
endif()