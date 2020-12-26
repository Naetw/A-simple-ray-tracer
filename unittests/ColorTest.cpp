#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "Albedo.h"
#include "Color.h"

TEST_CASE("Trival operations (getter)") {
    Color c1(19.22, -11.13, 12.02);

    REQUIRE(c1.r() == 19.22);
    REQUIRE(c1.g() == -11.13);
    REQUIRE(c1.b() == 12.02);
}

TEST_CASE("operator+=") {
    Color c1(2, 2, 2);
    Color c2(0.0, 3.3, 21.59);

    c1 += c2;
    REQUIRE(c1.r() == 2.0);
    REQUIRE(c1.g() == 5.3);
    REQUIRE(c1.b() == 23.59);
}

TEST_CASE("operator+ on two colors") {
    Color c1(2, 2, 2);
    Color c2(0.0, 3.3, 21.59);

    const Color &c3 = c1 + c2;
    REQUIRE(c3.r() == 2.0);
    REQUIRE(c3.g() == 5.3);
    REQUIRE(c3.b() == 23.59);
}

TEST_CASE("operator- on two colors") {
    Color c1(6.0, -8.0, 10.0);
    Color c2(3.0, -4.0, 5.0);

    const Color &c3 = c1 - c2;
    REQUIRE(c3.r() == 3.0);
    REQUIRE(c3.g() == -4.0);
    REQUIRE(c3.b() == 5.0);
}

TEST_CASE("operator* on the albedo and a color") {
    Albedo a(0.5, 0.5, 0.5);
    Color c(1, 1, 1);

    // only 50% of color has been reflected
    const Color &reflected_color = a * c;
    REQUIRE(reflected_color.r() == 0.5);
    REQUIRE(reflected_color.g() == 0.5);
    REQUIRE(reflected_color.b() == 0.5);
}
