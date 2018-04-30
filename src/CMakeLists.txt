add_library(
        boids SHARED
        ${APP_PATH}/src/Forces/Global/GlobalForces.cpp
        ${APP_PATH}/src/Forces/Local/LocalForces.cpp
        ${APP_PATH}/src/Forces/Local/SpatialHash.cpp
        ${APP_PATH}/src/Boids/Boid.cpp
        ${APP_PATH}/src/Boids/BoidController.cpp
)

target_include_directories(
        boids PUBLIC
        ${CINDER_PATH}/include
        ${APP_PATH}/include
)


find_library(CINDER cinder HINTS ${CINDER_PATH}/lib/linux/x86_64/ogl/${CMAKE_BUILD_TYPE}/)
target_link_libraries(boids ${CINDER} boost_system)




