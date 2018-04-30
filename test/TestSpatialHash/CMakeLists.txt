include_directories(${APP_PATH}/include)
include_directories(${APP_PATH}/src)

add_executable(TestSpatialHash test_spatial_hash.cpp)

target_link_libraries(TestSpatialHash boids)

add_test(NAME TestSpatialHash COMMAND TestSpatialHash)

