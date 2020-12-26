#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "Sphere.h"
#include "Ray.h"

TEST_CASE("Trivial operation (getter)") {
    Sphere sphere(nullptr, Point3(0, 0, 2), 1.0);

    REQUIRE(sphere.center().x() == 0);
    REQUIRE(sphere.center().y() == 0);
    REQUIRE(sphere.center().z() == 2);

    REQUIRE(sphere.radius() == 1.0);
}

/// Assume a sphere is centered at (0, 0, 2) and has radius R = 1
/// and there are 3 rays for testing 3 situations (inside, outside, on), they
/// are:
///    - origin (0, 0, 0), direction (0, 0, 1)
///    - origin (0, 2, 0), direction (0, 0, 1)
///    - origin (0, 1, 0), direction (0, 0, 1)
/// respectively.
TEST_CASE("Method hit") {
    Ray inside_ray(Point3(0, 0, 0), Vector3(0, 0, 1));
    Ray outside_ray(Point3(0, 2, 0), Vector3(0, 0, 1));
    Ray on_ray(Point3(0, 1, 0), Vector3(0, 0, 1));

    Sphere sphere(nullptr, Point3(0, 0, 2), 1.0);

    REQUIRE(sphere.hit(inside_ray) == true);
    REQUIRE(sphere.hit(outside_ray) == false);
    REQUIRE(sphere.hit(on_ray) == true);
}

/// Assume a sphere is centered at (0, 0, 2) and has radius R = 1
/// Ray and corresponding hit point without considering valid interval:
///    - origin (0, 0, 0), direction (0, 0, 2): (0, 0, 1)
///    - origin (0, 2, 0), direction (0, 0, 2): (infinity, infinity, infinity)
///    - origin (0, 1, 0), direction (0, 0, 2): (0, 1, 2)
TEST_CASE("Method getHitRecord") {
    Ray inside_ray(Point3(0, 0, 0), Vector3(0, 0, 2));
    Ray outside_ray(Point3(0, 2, 0), Vector3(0, 0, 2));
    Ray on_ray(Point3(0, 1, 0), Vector3(0, 0, 2));

    Sphere sphere(nullptr, Point3(0, 0, 2), 1.0);

    // With maximum valid interval
    const HitRecord &inside_record = sphere.getHitRecord(inside_ray, 0, kInfinity);
    const HitRecord &outside_record = sphere.getHitRecord(outside_ray, 0, kInfinity);
    const HitRecord &on_record = sphere.getHitRecord(on_ray, 0, kInfinity);

    REQUIRE(inside_record.point.x() == 0);
    REQUIRE(inside_record.point.y() == 0);
    REQUIRE(inside_record.point.z() == 1);
    REQUIRE(inside_record.t == 0.5);
    REQUIRE(inside_record.material_ptr == nullptr);
    REQUIRE(inside_record.normal.x() == 0);
    REQUIRE(inside_record.normal.y() == 0);
    REQUIRE(inside_record.normal.z() == -1);

    REQUIRE(outside_record.point.x() == kInfinity);
    REQUIRE(outside_record.point.y() == kInfinity);
    REQUIRE(outside_record.point.z() == kInfinity);
    REQUIRE(outside_record.t == 0);
    REQUIRE(inside_record.material_ptr == nullptr);
    REQUIRE(outside_record.normal.x() == 0);
    REQUIRE(outside_record.normal.y() == 0);
    REQUIRE(outside_record.normal.z() == 0);

    REQUIRE(on_record.point.x() == 0);
    REQUIRE(on_record.point.y() == 1);
    REQUIRE(on_record.point.z() == 2);
    REQUIRE(on_record.t == 1);
    REQUIRE(inside_record.material_ptr == nullptr);
    REQUIRE(on_record.normal.x() == 0);
    REQUIRE(on_record.normal.y() == -1);
    REQUIRE(on_record.normal.z() == 0);

    // With some valid interval (inside_ray needs t >= 0.5)
    const HitRecord &record = sphere.getHitRecord(inside_ray, 0, 0.2);
    REQUIRE(record.point.x() == kInfinity);
    REQUIRE(record.point.y() == kInfinity);
    REQUIRE(record.point.z() == kInfinity);
    REQUIRE(record.t == 0);
    REQUIRE(inside_record.material_ptr == nullptr);
    REQUIRE(record.normal.x() == 0);
    REQUIRE(record.normal.y() == 0);
    REQUIRE(record.normal.z() == 0);
}
