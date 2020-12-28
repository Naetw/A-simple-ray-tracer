#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Albedo.h"
#include "Color.h"
#include "Point3.h"
#include "Vector3.h"

#include <functional>

class HittableList;
class Ray;

class Ray {
  private:
    Point3 m_origin;
    Vector3 m_direction;

  public:
    ~Ray() = default;

    Ray() = default;
    Ray(const Point3 &origin, const Vector3 &direction)
        : m_origin(origin), m_direction(direction) {}

    const Point3 &origin() const { return m_origin; }
    const Vector3 &direction() const { return m_direction; }

    Point3 at(double factor) const;

    /// Generate a color for the ray based on the `world`
    ///
    /// If the ray doesn't hit anything, we use a default background generator
    /// which generates a blend color of white and blue. Users can provide
    /// their own background generator.
    Color generateRayColor(
        const HittableList &world, uint32_t depth,
        std::function<Color(const Ray &)> generateBackgroundColor =
            [](const Ray &ray) {
                Color white_color(1.0, 1.0, 1.0);
                Color blue_color(0.5, 0.7, 1.0);

                const Vector3 &unit_direction = ray.direction().getUnitVector();

                // generated color bases on coordinate y
                // first, normalize y from -1.0 ~ 1.0 to 0.0 ~ 1.0
                // then, when normalized y is 1.0, use blue; while 0.0, use
                // white
                auto t = 0.5 * (unit_direction.y() + 1.0);

                // blend the white and blue
                return Albedo(1.0 - t) * white_color + Albedo(t) * blue_color;
            }) const;

    /// Return true if m_direction is (0, 0, 0) which means that this isn't a
    /// valid ray.
    bool operator!() const;

  public:
    static Vector3 getReflectedRay(const Ray &ray, const Vector3 &normal);
    static Vector3 getRefractedRay(const Ray &ray, const Vector3 &normal,
                                   double refraction_ratio);
};

#endif
