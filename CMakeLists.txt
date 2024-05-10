cmake_minimum_required(VERSION 3.16)
project(220229053_SenaNurDulger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp)
add_executable(220229053_SenaNurDulger ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(220229053_SenaNurDulger sfml-system sfml-window sfml-graphics sfml-audio sfml-network)