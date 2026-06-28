cmake_minimum_required(VERSION 3.16)
project(robot_state_estimator_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_library(estimator_lib
    src/StateEstimator.cpp
    src/SensorHealth.cpp
)

add_executable(robot_state_estimator src/main.cpp)
target_link_libraries(robot_state_estimator estimator_lib)

add_executable(estimator_tests tests/estimator_tests.cpp)
target_link_libraries(estimator_tests estimator_lib)
