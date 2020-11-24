#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include "Point3.h"
#include "Ray.h"
#include "Utility.h"
#include "Vector3.h"

struct HitRecord {
  public:
    Point3 point;
    double t;
    Vector3 normal;

  public:
    ~HitRecord() = default;

    HitRecord() : point(kInfinity, kInfinity, kInfinity) {}
    HitRecord(const Point3 &p, double t) : point(p.x(), p.y(), p.z()), t(t) {}

    /// Set the normal vector against the direction of the given ray based on
    /// the given intersection point
    void setFaceNormalVector(const Ray &ray, const Vector3 &outward_normal) {
        normal = (dot(ray.direction(), outward_normal) < 0) ? outward_normal
                                                            : -outward_normal;
    }
};

class Hittable {
  public:
    /// Determine whether the passed-in ray hits the Hittable object
    virtual bool hit(const Ray &ray) const = 0;

    /// Ray can extend through factor t: origin + t * direction
    /// t_min & t_max here is for having a valid interval for the ray
    /// extension.
    /// Return
    ///     Point3(infinity, infinity, infinity)
    ///     Vector3()
    ///     double()
    /// if there's no hit point.
    virtual HitRecord getHitRecord(const Ray &ray, double t_min,
                                   double t_max) const = 0;
};

#endif
