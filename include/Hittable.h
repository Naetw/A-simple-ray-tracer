#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include "Point3.h"
#include "Ray.h"
#include "Utility.h"
#include "Vector3.h"

#include <memory>

class Material;

struct HitRecord {
  public:
    Point3 point;
    double t;
    const Material *material_ptr;
    Vector3 normal;
    // represent whether a ray is from outside (true) or inside (false)
    bool front_face;

  public:
    ~HitRecord() = default;

    HitRecord()
        : point(kInfinity, kInfinity, kInfinity), t(0), material_ptr(nullptr),
          front_face(true) {}
    HitRecord(const Point3 &p, double t, const Material *mp)
        : point(p.x(), p.y(), p.z()), t(t), material_ptr(mp), front_face(true) {}

    /// Set the normal vector against the direction of the given ray based on
    /// the given intersection point
    void setFaceNormalVector(const Ray &ray, const Vector3 &outward_normal) {
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

using MaterialSharedPtr = std::shared_ptr<Material>;

class Hittable {
  private:
    MaterialSharedPtr material_shared_ptr;

  public:
    ~Hittable() = default;

    Hittable() : material_shared_ptr(nullptr) {}
    Hittable(const MaterialSharedPtr &msp) : material_shared_ptr(msp) {}

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

    const Material *getMaterialPointer() const {
        return material_shared_ptr.get();
    }
};

#endif
