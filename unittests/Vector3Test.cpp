#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "Vector3.h"

#include <cmath>

TEST_CASE("Trival operations (getter)") {
    Vector3 v1(19.22, -11.13, 12.02);

    REQUIRE(v1.x() == 19.22);
    REQUIRE(v1.y() == -11.13);
    REQUIRE(v1.z() == 12.02);
}

TEST_CASE("Method squaredLength") {
    Vector3 v1(3.0, 4.0, 0.0);
    Vector3 v2(26.5, -100, 0.4);

    REQUIRE(v1.squaredLength() == 25.0);
    REQUIRE(v2.squaredLength() == (26.5 * 26.5) + (-100 * -100) + (0.4 * 0.4));
}

TEST_CASE("Method length") {
    Vector3 v1(3.0, 4.0, 0.0);
    Vector3 v2(26.5, -100, 0.4);

    REQUIRE(v1.length() == 5);
    REQUIRE(v2.length() == sqrt((26.5 * 26.5) + (-100 * -100) + (0.4 * 0.4)));
}

TEST_CASE("Method getUnitVector") {
    Vector3 v1(3.0, -4.0, 5.0);
    Vector3 v2(6.0, -8.0, 10.0);

    REQUIRE(v1.getUnitVector().x() == v2.getUnitVector().x());
    REQUIRE(v1.getUnitVector().y() == v2.getUnitVector().y());
    REQUIRE(v1.getUnitVector().z() == v2.getUnitVector().z());
}

TEST_CASE("Method nearZero") {
    Vector3 v1(3.0, -4.0, 5.0);
    Vector3 v2(1e-12, 1e-2, 1e-8);
    Vector3 v3(1e-12, 1e-12, 1e-14);

    REQUIRE(v1.nearZero() == false);
    REQUIRE(v2.nearZero() == false);
    REQUIRE(v3.nearZero() == true);
}

TEST_CASE("operator+ on two vectors") {
    Vector3 v1(2, 2, 2);
    Vector3 v2(0.0, 3.3, 21.59);

    const Vector3 &v3 = v1 + v2;
    REQUIRE(v3.x() == 2.0);
    REQUIRE(v3.y() == 5.3);
    REQUIRE(v3.z() == 23.59);
}

TEST_CASE("operator- on a vector") {
    Vector3 v1(2, 2, 2);

    const Vector3 &v2 = -v1;
    REQUIRE(v2.x() == -2);
    REQUIRE(v2.y() == -2);
    REQUIRE(v2.z() == -2);
}

TEST_CASE("operator* on two vectors") {
    Vector3 v1(2, 2, 2);
    Vector3 v2(0.0, 3.3, 21.59);

    const Vector3 &v3 = v1 * v2;
    REQUIRE(v3.x() == 0.0);
    REQUIRE(v3.y() == 6.6);
    REQUIRE(v3.z() == 43.18);
}

TEST_CASE("operator/ on two vectors") {
    Vector3 v1(6.0, -8.0, 10.0);
    Vector3 v2(3.0, -4.0, 5.0);

    const Vector3 &v3 = v1 / v2;
    REQUIRE(v3.x() == 2.0);
    REQUIRE(v3.y() == 2.0);
    REQUIRE(v3.z() == 2.0);
}
