#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "Hittable.h"
#include "Metal.h"

TEST_CASE("Method getScatteredRay") {
    Ray ray(Point3(0, 10, 0), Vector3(2, -8, 0));
    Vector3 normal(0, 1, 0);
    HitRecord record;
    Metal metal;

    record.point = Point3(2, 2, 0);
    record.normal = normal;

    const Ray &scattered_ray = metal.getScatteredRay(ray, record);
    REQUIRE(scattered_ray.origin().x() == record.point.x());
    REQUIRE(scattered_ray.origin().y() == record.point.y());
    REQUIRE(scattered_ray.origin().z() == record.point.z());
    REQUIRE(scattered_ray.direction().x() == ray.direction().x());
    REQUIRE(scattered_ray.direction().y() == ray.direction().y() * -1);
    REQUIRE(scattered_ray.direction().z() == ray.direction().z());
}
