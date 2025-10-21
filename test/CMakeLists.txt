project(Google_tests)

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE TEST_SOURCES
        "${CMAKE_SOURCE_DIR}/lib/*.cpp"
)
file(GLOB_RECURSE TESTS
        vec3-test.cpp
        matrix3x3-test.cpp
        camera-test.cpp
)
add_executable(test ${TESTS} ${TEST_SOURCES}
        )
target_link_libraries(test gtest gtest_main)