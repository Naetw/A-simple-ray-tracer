#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "Sphere.h"
#include "Ray.h"

/// Assume a sphere is centered at (0, 0, 2) and has radius R = 1
/// and there are 3 rays for testing 3 situations (inside, outside, on), they
/// are:
///    - origin (0, 0, 0), direction (0, 0, 1)
///    - origin (0, 2, 0), direction (0, 0, 1)
///    - origin (0, 1, 0), direction (0, 0, 1)
/// respectively.
TEST_CASE("Method calculateDiscriminant") {
    Ray inside_ray(Point3(0, 0, 0), Vector3(0, 0, 1));
    Ray outside_ray(Point3(0, 2, 0), Vector3(0, 0, 1));
    Ray on_ray(Point3(0, 1, 0), Vector3(0, 0, 1));

    Sphere sphere(Point3(0, 0, 2), 1.0);

    REQUIRE(sphere.calculateDiscriminant(inside_ray) > 0.0);
    REQUIRE(sphere.calculateDiscriminant(outside_ray) < 0.0);
    REQUIRE(sphere.calculateDiscriminant(on_ray) == 0.0);
}

/// Refer to the assumption of "Method calculateDiscriminant" test case
TEST_CASE("Method hit") {
    Ray inside_ray(Point3(0, 0, 0), Vector3(0, 0, 1));
    Ray outside_ray(Point3(0, 2, 0), Vector3(0, 0, 1));
    Ray on_ray(Point3(0, 1, 0), Vector3(0, 0, 1));

    Sphere sphere(Point3(0, 0, 2), 1.0);

    REQUIRE(sphere.hit(inside_ray) == true);
    REQUIRE(sphere.hit(outside_ray) == false);
    REQUIRE(sphere.hit(on_ray) == true);
}
