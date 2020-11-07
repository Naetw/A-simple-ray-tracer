#include "Color.h"
#include "Point3.h"
#include "Ray.h"
#include "Vector3.h"

#include <cstdint>
#include <iostream>

// FIXME: this should be a method in class Ray. Maybe need a parameter of
//        object for determining the pixel color
Color genRayColor(const Ray &r) {
    auto unit_direction = r.direction().getUnitVector();

    // generated color bases on coordinate y
    // first, normalize y from -1.0 ~ 1.0 to 0.0 ~ 1.0
    // then, when normalized y is 1.0, use blue; while 0.0, use white
    auto t = 0.5 * (unit_direction.y() + 1.0);
    Color white(1.0, 1.0, 1.0);
    Color blue(0.5, 0.7, 1.0);

    // blend the white and blue
    return (1.0 - t) * white + t * blue;
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int32_t image_width = 400;
    const auto image_height = static_cast<int32_t>(image_width / aspect_ratio);

    // Camera
    // FIXME: This should be modularized.
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal_vec = Vector3(viewport_width, 0, 0);
    auto vertical_vec = Vector3(0, viewport_height, 0);
    // origin + (0, 0, focal_length) == center of the viewport
    auto lower_left_corner = origin - (horizontal_vec / 2) -
                             (vertical_vec / 2) - Vector3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (auto j = image_height - 1; j >= 0; --j) {
        for (int32_t i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray ray(origin, lower_left_corner + u * horizontal_vec +
                                v * vertical_vec - origin);
            auto pixel_color = genRayColor(ray);

            writeColorToStream(std::cout, pixel_color);
        }
    }
}
