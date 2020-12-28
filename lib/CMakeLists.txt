add_library(raytracer_core STATIC
    Color.cpp
    Point3.cpp
    Ray.cpp
    Vector3.cpp
    Sphere.cpp
    HittableList.cpp
    Utility.cpp
    Lambertian.cpp
    Metal.cpp
    Dielectric.cpp
    Camera.cpp)

target_compile_options(raytracer_core PRIVATE -fopenmp)
target_link_libraries(raytracer_core -fopenmp)
