cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)

get_filename_component(APP_PATH "." ABSOLUTE)
get_filename_component(CINDER_PATH "/home/micha/Cinder" ABSOLUTE)

project(boids_app)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)

include_directories(
        ${CINDER_PATH}/include
        ${APP_PATH}/include
)

add_executable(
        boids_app
        app.cpp
)

target_link_libraries(boids_app boids)

