cmake_minimum_required(VERSION 4.0)
project(cgr_raytracer)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
        main.cpp
        lib/utils/logger.cpp
        lib/raytracer_app.cpp
        lib/utils/ppm_image.cpp
        lib/math/vec3.cpp
        lib/math/color.cpp
        lib/math/camera.cpp
        lib/math/ray.cpp
        lib/scene.cpp
        lib/utils/args-parser.cpp
)

add_executable(cgr-raytracer ${SOURCES})
