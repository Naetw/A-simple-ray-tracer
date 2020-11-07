cmake_minimum_required(VERSION 3.10)
enable_testing()

# set the project name
project(RayTracer)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify the C++ compiler
set(CMAKE_CXX_COMPILER clang++)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(lib)

# add the executable
add_executable(raytracer main.cpp)

target_link_libraries(raytracer raytracer_core)

# ------------------------
# > Test
# ------------------------

add_subdirectory(unittests)
