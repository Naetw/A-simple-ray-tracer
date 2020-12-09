#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Point3.h"
#include "Vector3.h"

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

    /// Return true if m_direction is (0, 0, 0) which means that this isn't a
    /// valid ray.
    bool operator!() const;

  public:
    static Vector3 getReflectedRay(const Ray &ray, const Vector3 &normal);
    static Vector3 getRefractedRay(const Ray &ray, const Vector3 &normal,
                                   double refraction_ratio);
};

#endif
