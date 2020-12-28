#include "Color.h"
#include "Albedo.h"
#include "Utility.h"

#include <cstdint>

Color &Color::operator+=(const Color &other_color) {
    m_pixel[0] += other_color.r();
    m_pixel[1] += other_color.g();
    m_pixel[2] += other_color.b();
    return *this;
}

Color operator+(const Color &color1, const Color &color2) {
    return Color(color1.r() + color2.r(),
                 color1.g() + color2.g(),
                 color1.b() + color2.b());
}

Color operator-(const Color &color1, const Color &color2) {
    return Color(color1.r() - color2.r(),
                 color1.g() - color2.g(),
                 color1.b() - color2.b());
}

Color operator*(const Albedo &attenuation, const Color &color) {
    return Color(attenuation.r() * color.r(),
                 attenuation.g() * color.g(),
                 attenuation.b() * color.b());
}
