#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "Camera.h"

TEST_CASE("Method getRay") {
    Point3 origin(2, 2, 2);
    double focal_length = 4;
    double aspect_ratio = 2;
    Camera camera(origin, aspect_ratio, 90.0, focal_length);

    const Ray &ray = camera.getRay(0.25, 0.3);

    const double width = 16;
    const double height = 8;
    const Point3 lower_left_corner(origin.x() - (width / 2), origin.y() - (height / 2), origin.z() - focal_length);
    const Ray answer(origin, lower_left_corner + Vector3(0.25 * width, 0, 0) + Vector3(0, 0.3 * height, 0) - origin);

    REQUIRE(ray.origin().x() == answer.origin().x());
    REQUIRE(ray.origin().y() == answer.origin().y());
    REQUIRE(ray.origin().z() == answer.origin().z());
    REQUIRE(ray.direction().x() == Approx(answer.direction().x()));
    REQUIRE(ray.direction().y() == Approx(answer.direction().y()));
    REQUIRE(ray.direction().z() == Approx(answer.direction().z()));
}

