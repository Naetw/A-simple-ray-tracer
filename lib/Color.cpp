#include "Color.h"

#include <cstdint>

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

void writeColorToStream(std::ostream &out, const Color &pixel_color) {
    // write the translated [0,255] value of each color component.
    out << static_cast<uint32_t>(255.999 * pixel_color.r()) << ' '
        << static_cast<uint32_t>(255.999 * pixel_color.g()) << ' '
        << static_cast<uint32_t>(255.999 * pixel_color.b()) << '\n';
}

