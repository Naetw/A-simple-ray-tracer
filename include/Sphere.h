#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Hittable.h"
#include "Point3.h"

class Ray;

class Sphere : public Hittable {
  private:
    Point3 m_center;
    double m_radius;

  public:
    ~Sphere() = default;

    Sphere() = default;
    Sphere(const Point3 &c, const double r) : m_center(c), m_radius(r) {}

    /// This method calculates the discriminant (b^2 - 4ac) according to
    /// passed-in Ray
    double calculateDiscriminant(const Ray& ray) const;

    /// This method just uses the result of method
    /// calculateDiscriminant to determine whether there's a hit
    virtual bool hit(const Ray& ray) const override;
};

#endif
