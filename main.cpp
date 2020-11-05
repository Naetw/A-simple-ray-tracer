#include "Color.h"

#include <cstdint>
#include <iostream>

int main() {

    // Image

    const int32_t image_width = 256;
    const int32_t image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (auto j = image_height - 1; j >= 0; --j) {
        for (int32_t i = 0; i < image_width; ++i) {
            Color pixel_color(double(i) / (image_width - 1),
                              double(j) / (image_height - 1),
                              0.25);

            writeColorToStream(std::cout, pixel_color);
        }
    }
}
