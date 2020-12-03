#include "Color.h"
#include "Utility.h"

#include <cstdint>
#include <cmath>

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

Color operator*(const Color &factor, const Color &color) {
    return Color(factor.r() * color.r(),
                 factor.g() * color.g(),
                 factor.b() * color.b());
}

void writeColorToStream(std::ostream &out, const Color &pixel_color, const uint32_t samples_per_pixel) {
    double r = pixel_color.r();
    double g = pixel_color.g();
    double b = pixel_color.b();

    // divide the color by # of samples and gamma-correct for gamma=2.0
    auto scale = 1.0 / samples_per_pixel;
    auto gamma = 2.0;
    r = pow(scale * r, 1 / gamma);
    g = pow(scale * g, 1 / gamma);
    b = pow(scale * b, 1 / gamma);

    // write the translated [0,255] value of each color component.
    out << static_cast<uint32_t>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<uint32_t>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<uint32_t>(256 * clamp(b, 0.0, 0.999)) << '\n';
}
