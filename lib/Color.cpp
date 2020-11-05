#include "Color.h"

void writeColorToStream(std::ostream &out, const Color &pixel_color) {
    // write the translated [0,255] value of each color component.
    out << static_cast<uint32_t>(255.999 * pixel_color.r()) << ' '
        << static_cast<uint32_t>(255.999 * pixel_color.g()) << ' '
        << static_cast<uint32_t>(255.999 * pixel_color.b()) << '\n';
}

