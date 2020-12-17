#include "Camera.h"
#include "Color.h"
#include "Dielectric.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Lambertian.h"
#include "Material.h"
#include "Metal.h"
#include "Point3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Utility.h"
#include "Vector3.h"

#include <cstdint>
#include <iostream>

// FIXME: this should be a method in class Ray. Maybe need a parameter of
//        object for determining the pixel color
Color genRayColor(const Ray &r, const HittableList &world, uint32_t depth) {
    if (depth == 0) {
        // if we've exceeded the ray bounce limit, no more light is gathered.
        return /* black */ Color(0, 0, 0);
    }

    Color white_color(1.0, 1.0, 1.0);
    Color blue_color(0.5, 0.7, 1.0);

    // 0.001 for ignoring the hits that the `t` is very close to 0
    const HitRecord &record = world.getHitRecord(r, 0.001, kInfinity);
    if (!record.point.isInfinity()) {
        const Ray &scattered_ray = record.material_ptr->getScatteredRay(r, record);
        if (!scattered_ray) {
            // all rays have been absorbed
            return /* black */ Color(0, 0, 0);
        }
        // attenuation determins what proportion of ray being absorbed
        const Albedo &attenuation = record.material_ptr->getAlbedo();
        return attenuation * genRayColor(scattered_ray, world, depth - 1);
    }

    //
    // background
    //
    auto unit_direction = r.direction().getUnitVector();

    // generated color bases on coordinate y
    // first, normalize y from -1.0 ~ 1.0 to 0.0 ~ 1.0
    // then, when normalized y is 1.0, use blue; while 0.0, use white
    auto t = 0.5 * (unit_direction.y() + 1.0);

    // blend the white and blue
    return (1.0 - t) * white_color + t * blue_color;
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int32_t image_width = 400;
    const auto image_height = static_cast<int32_t>(image_width / aspect_ratio);
    const uint32_t samples_per_pixel = 100;
    const uint32_t max_depth = 50;

    // World
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Albedo(0.8, 0.8, 0.0));
    auto center_material = std::make_shared<Lambertian>(Albedo(0.1, 0.2, 0.5));
    auto left_material = std::make_shared<Dielectric>(1.5);
    auto right_material = std::make_shared<Metal>(Albedo(0.8, 0.6, 0.2), /* fuzziness */ 0.0);

    world.add(std::make_shared<Sphere>(center_material, Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(ground_material, Point3(0, -100.5, -1), 100));
    world.add(std::make_shared<Sphere>(left_material, Point3(-1, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(left_material, Point3(-1, 0, -1), -0.45));
    world.add(std::make_shared<Sphere>(right_material, Point3(1, 0, -1), 0.5));

    Point3 origin(3, 3, 2);
    Point3 look_at(0, 0, -1);

    Camera camera(origin, look_at,
                  /* view up */ Vector3(0, 1, 0), aspect_ratio,
                  /* angle_of_vertical_fov */ 20, /* aperture */ 2.0,
                  /* focus_distance */ (origin - look_at).length());

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (auto j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rRemaining: " << j << ' ' << std::flush;
        for (int32_t i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);

            // use multiple samples and random real numbers to blend the colors
            // of adjacent pixels, in this way, we can achieve simple
            // antialiasing
            for (uint32_t s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + getRandomDouble01()) / (image_width - 1);
                auto v = (j + getRandomDouble01()) / (image_height - 1);
                const Ray &ray = camera.getRay(u, v);
                pixel_color += genRayColor(ray, world, max_depth);
            }

            writeColorToStream(std::cout, pixel_color, samples_per_pixel);
        }
    }
}
