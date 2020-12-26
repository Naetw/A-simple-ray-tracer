#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "Ray.h"

TEST_CASE("Trival operations (getter)") {
    Point3 p1(19.22, -11.13, 12.02);
    Vector3 v1(20.20, 11.07, 22.18);
    Ray r1(p1, v1);

    REQUIRE(r1.origin().x() == 19.22);
    REQUIRE(r1.origin().y() == -11.13);
    REQUIRE(r1.origin().z() == 12.02);
    REQUIRE(r1.direction().x() == 20.20);
    REQUIRE(r1.direction().y() == 11.07);
    REQUIRE(r1.direction().z() == 22.18);
}

TEST_CASE("Method at") {
    Point3 p1(19.22, -11.13, 12.02);
    Vector3 v1(20.20, 11.07, 22.18);
    Ray r1(p1, v1);

    const Point3 &p2 = r1.at(11);
    REQUIRE(p2.x() == 19.22 + 11 * 20.20);
    REQUIRE(p2.y() == -11.13 + 11 * 11.07);
    REQUIRE(p2.z() == 12.02 + 11 * 22.18);
}

