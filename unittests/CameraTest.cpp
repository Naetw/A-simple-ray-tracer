#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "Camera.h"

TEST_CASE("Method getRay") {
    Point3 origin(2, 2, 2);
    double focus_distance = 4;
    double aspect_ratio = 2;
    Camera camera(origin, origin + Vector3(0, 0, -focus_distance), Vector3(0, 1, 0),
                  aspect_ratio, 90.0, 0, focus_distance);

    const Ray &ray = camera.getRay(0.25, 0.3);

    const double width = 16;
    const double height = 8;
    const Point3 lower_left_corner(origin.x() - (width / 2),
                                   origin.y() - (height / 2),
                                   // length from origin to viewport in z-axis
                                   origin.z() - Vector3(0, 0, focus_distance).z());
    const Ray answer(origin, lower_left_corner + Vector3(0.25 * width, 0, 0) + Vector3(0, 0.3 * height, 0) - origin);

    REQUIRE(ray.origin().x() == answer.origin().x());
    REQUIRE(ray.origin().y() == answer.origin().y());
    REQUIRE(ray.origin().z() == answer.origin().z());

    const Vector3 &unit_ray_direction = ray.direction().getUnitVector();
    const Vector3 &unit_answer_direction = answer.direction().getUnitVector();

    REQUIRE(unit_ray_direction.x() == Approx(unit_answer_direction.x()));
    REQUIRE(unit_ray_direction.y() == Approx(unit_answer_direction.y()));
    REQUIRE(unit_ray_direction.z() == Approx(unit_answer_direction.z()));
}

