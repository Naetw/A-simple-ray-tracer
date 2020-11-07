#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "Vector3.h"
#include "Point3.h"

TEST_CASE("Trival operation (getter)") {
    Point3 p1(19.22, -11.13, 12.02);

    REQUIRE(p1.x() == 19.22);
    REQUIRE(p1.y() == -11.13);
    REQUIRE(p1.z() == 12.02);
}

TEST_CASE("operator+ on a point and a vector") {
    Point3 p1(-2, 1, -10);
    Vector3 v1(3.0, 4.0, 5.0);

    Point3 p2 = p1 + v1;
    REQUIRE(p2.x() == (-2 + 3.0));
    REQUIRE(p2.y() == (1 + 4.0));
    REQUIRE(p2.z() == (-10 + 5.0));
}

TEST_CASE("operator- on a point and a vector") {
    Point3 p1(-2, 1, -10);
    Vector3 v1(3.0, 4.0, 5.0);

    Point3 p2 = p1 - v1;
    REQUIRE(p2.x() == (-2 - 3.0));
    REQUIRE(p2.y() == (1 - 4.0));
    REQUIRE(p2.z() == (-10 - 5.0));
}

TEST_CASE("operator- on two points") {
    Point3 p1(-2, 1, -10);
    Point3 p2(3.0, 4.0, 5.0);

    Vector3 v1 = p1 - p2;
    REQUIRE(v1.x() == (-2 - 3.0));
    REQUIRE(v1.y() == (1 - 4.0));
    REQUIRE(v1.z() == (-10 - 5.0));
}
