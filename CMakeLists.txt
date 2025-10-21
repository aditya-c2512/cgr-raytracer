cmake_minimum_required(VERSION 4.0)
project(cgr_raytracer)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp"
        "${CMAKE_SOURCE_DIR}/main.cpp"
)

add_subdirectory(test)

add_executable(cgr-raytracer ${SOURCES})
