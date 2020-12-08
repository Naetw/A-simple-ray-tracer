find_package(Catch2 REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

function(add_raytracer_test name)
    add_executable(unittest_${name} ${ARGN})
    target_link_libraries(unittest_${name} raytracer_core Catch2::Catch2)
    add_test(${name} unittest_${name})
endfunction()

add_raytracer_test(Vector3 Vector3Test.cpp)
add_raytracer_test(Point3 Point3Test.cpp)
add_raytracer_test(Color ColorTest.cpp)
add_raytracer_test(Ray RayTest.cpp)
add_raytracer_test(Sphere SphereTest.cpp)
add_raytracer_test(HittableList HittableListTest.cpp)
add_raytracer_test(Camera CameraTest.cpp)
add_raytracer_test(Metal MetalTest.cpp)
