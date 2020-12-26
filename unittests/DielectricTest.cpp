#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "Dielectric.h"
#include "Hittable.h"

#include <cmath>

TEST_CASE("Method getScatteredRay") {
    // A ray with incident angle - 60 degree and refraction angle 30 degree
    auto sqrt_3 = sqrt(3);
    Ray ray(Point3(-sqrt_3, 1, 0), Vector3(sqrt_3, -1, 0));
    Vector3 normal(0, 1, 0);
    HitRecord record;

    record.point = Point3(0, 0, 0);
    record.normal = normal;

    Dielectric dielectric1(sqrt_3);
    const Ray &scattered_ray1 = dielectric1.getScatteredRay(ray, record);
    REQUIRE(scattered_ray1.origin().x() == record.point.x());
    REQUIRE(scattered_ray1.origin().y() == record.point.y());
    REQUIRE(scattered_ray1.origin().z() == record.point.z());
    REQUIRE(scattered_ray1.direction().x() == Approx((ray.direction().y() / ray.direction().length()) * -1));
    REQUIRE(scattered_ray1.direction().y() == Approx((ray.direction().x() / ray.direction().length()) * -1));
    REQUIRE(scattered_ray1.direction().z() == ray.direction().z());

    // A ray with incident angle - 60 degree and reflection angle 60 degree
    // 0.5 for smaller than air's refraction index 1.0
    Dielectric dielectric2(0.5);
    const Ray &scattered_ray2 = dielectric2.getScatteredRay(ray, record);
    REQUIRE(scattered_ray2.origin().x() == record.point.x());
    REQUIRE(scattered_ray2.origin().y() == record.point.y());
    REQUIRE(scattered_ray2.origin().z() == record.point.z());
    REQUIRE(scattered_ray2.direction().x() == ray.direction().x());
    REQUIRE(scattered_ray2.direction().y() == ray.direction().y() * -1);
    REQUIRE(scattered_ray2.direction().z() == ray.direction().z());
}
