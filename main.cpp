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

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int32_t image_width = 400;
    const auto image_height = static_cast<int32_t>(image_width / aspect_ratio);

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
                  /* angle_of_vertical_fov */ 20, /* aperture */ 0.1,
                  /* focus_distance */ 10,
                  /* samples_per_pixel */ 100,
                  /* max_depth */ 50);

    // Render
    camera.renderImageToOstream(image_width, image_height, world, std::cout);
}
