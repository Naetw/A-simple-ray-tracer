#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "Camera.h"

TEST_CASE("Method getRay") {
    Point3 origin(2, 2, 2);
    Camera camera(origin, 4 / 2, 4, 3);

    const Ray &ray = camera.getRay(0.25, 0.3);
    const Point3 lower_left_corner(-2, 0, -1);
    const Ray answer(origin, lower_left_corner + Vector3(0.25 * 8, 0, 0) + Vector3(0, 0.3 * 4, 0) - origin);

    REQUIRE(ray.origin().x() == answer.origin().x());
    REQUIRE(ray.origin().y() == answer.origin().y());
    REQUIRE(ray.origin().z() == answer.origin().z());
    REQUIRE(ray.direction().x() == answer.direction().x());
    REQUIRE(ray.direction().y() == answer.direction().y());
    REQUIRE(ray.direction().z() == answer.direction().z());
}

