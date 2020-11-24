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

    const Point3 &center() const { return m_center; }
    double radius() const { return m_radius; }

    /// This method just uses the result of static helper function
    /// calculateDiscriminant to determine whether there's a hit
    virtual bool hit(const Ray &ray) const override;

    virtual HitRecord getHitRecord(const Ray &ray, double t_min,
                                   double t_max) const override;
};

#endif
