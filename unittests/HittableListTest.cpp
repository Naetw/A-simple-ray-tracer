#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "HittableList.h"
#include "Sphere.h"

/// Assume two spheres are centered at (0, 0, 2), (0, 0, 6) and both have radius R = 1
/// and there is a ray for testing, it is:
///    - origin (0, 0, 0), direction (0, 0, 2)
TEST_CASE("Method getHitRecord") {
    std::shared_ptr<Hittable> obj1 = std::make_shared<Sphere>(nullptr, Point3(0, 0, 2), 1.0);
    std::shared_ptr<Hittable> obj2 = std::make_shared<Sphere>(nullptr, Point3(0, 0, 6), 1.0);
    HittableList world;

    world.add(obj1);
    world.add(obj2);

    Ray inside_ray(Point3(0, 0, 0), Vector3(0, 0, 2));
    const HitRecord &hit_1st_sphere_record = world.getHitRecord(inside_ray, 0, kInfinity);
    const HitRecord &hit_2nd_sphere_record = world.getHitRecord(inside_ray, 2, kInfinity);

    REQUIRE(hit_1st_sphere_record.point.x() == 0);
    REQUIRE(hit_1st_sphere_record.point.y() == 0);
    REQUIRE(hit_1st_sphere_record.point.z() == 1);
    REQUIRE(hit_1st_sphere_record.t == 0.5);
    REQUIRE(hit_1st_sphere_record.normal.x() == 0);
    REQUIRE(hit_1st_sphere_record.normal.y() == 0);
    REQUIRE(hit_1st_sphere_record.normal.z() == -1);

    REQUIRE(hit_2nd_sphere_record.point.x() == 0);
    REQUIRE(hit_2nd_sphere_record.point.y() == 0);
    REQUIRE(hit_2nd_sphere_record.point.z() == 5);
    REQUIRE(hit_2nd_sphere_record.t == 2.5);
    REQUIRE(hit_2nd_sphere_record.normal.x() == 0);
    REQUIRE(hit_2nd_sphere_record.normal.y() == 0);
    REQUIRE(hit_2nd_sphere_record.normal.z() == -1);
}
