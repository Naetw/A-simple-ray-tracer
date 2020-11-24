#ifndef RAYTRACER_HITTABLE_LIST_H
#define RAYTRACER_HITTABLE_LIST_H

#include "Hittable.h"
#include "Point3.h"
#include "Vector3.h"

#include <vector>
#include <memory>

class Ray;

/// This class is used for representing the world in the scene. That is,
/// it contains all objects in the scene. We then can use a camera to render
/// the whole image through casting rays on "the world".
class HittableList {
  private:
    std::vector<std::shared_ptr<Hittable>> m_objects;

  public:
    ~HittableList() = default;

    HittableList() = default;

    void add(std::shared_ptr<Hittable> object);

    /// Return the record of the first hit point among m_objects
    ///
    /// Ray is in the form of A + tb where A and b are constant while t is
    /// dynamic. t_min and t_max determine the range of valid t
    HitRecord getHitRecord(const Ray &ray, double t_min, double t_max) const;
};

#endif
