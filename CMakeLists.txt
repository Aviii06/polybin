cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0091 NEW)

project(polybin)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")

add_executable(${PROJECT_NAME} main.cpp ${HEADER_FILES} ${SOURCE_FILES})

add_subdirectory(vendor)
target_link_libraries(${PROJECT_NAME} polyscope)
