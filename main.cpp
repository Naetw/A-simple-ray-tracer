#include "Camera.h"
#include "Color.h"
#include "Dielectric.h"
#include "HittableList.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Point3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector3.h"

#include <cstdint>
#include <iostream>

HittableList getRandomScene() {
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Albedo(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(ground_material, Point3(0, -1000, 0), 1000));

    // place 3 main big spheres at the center of images
    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(material1, Point3(0, 1, 0), 1.0));

    auto material2 = std::make_shared<Lambertian>(Albedo(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(material2, Point3(-4, 1, 0), 1.0));

    auto material3 = std::make_shared<Metal>(Albedo(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(material3, Point3(4, 1, 0), 1.0));

    // select a base coordinate at x-axis (-11 - 10)
    for (int64_t a = -11; a < 11; ++a) {
        // generate 11 - -11 (22) spheres around the a in x-axis
        // they are differed in z-axis
        for (int64_t b = -11; b < 11; ++b) {
            Point3 center(a + 0.9 * getRandomDouble01(),
                          0.2,
                          b + 0.9 * getRandomDouble01());

			// make sure the random sphere is not within the 3 main big spheres
            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                MaterialSharedPtr sphere_material;

                auto choose_material = getRandomDouble01();
                if (choose_material < 0.8) {
                    // diffuse
                    auto albedo = Vector3::getRandomVector() * Vector3::getRandomVector();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                } else if (choose_material < 0.95) {
                    // metal
                    auto albedo = Vector3::getRandomVector(0.5, 1);
                    auto fuzz = getRandomDoubleInRange(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                }

                world.add(std::make_shared<Sphere>(sphere_material, center, 0.2));
            }

        }
    }

    return world;
}

int main() {

    // Image
    const auto aspect_ratio = 3.0 / 2.0;
    const int32_t image_width = 1200;
    const auto image_height = static_cast<int32_t>(image_width / aspect_ratio);

    // World
    HittableList world = getRandomScene();

    Point3 origin(13, 2, 3);
    Point3 look_at(0, 0, 0);

    Camera camera(origin, look_at,
                  /* view up */ Vector3(0, 1, 0), aspect_ratio,
                  /* angle_of_vertical_fov */ 20, /* aperture */ 0.1,
                  /* focus_distance */ 10,
                  /* samples_per_pixel */ 500,
                  /* max_depth */ 50);

    // Render
    camera.renderImageToOstream(image_width, image_height, world, std::cout);
}
