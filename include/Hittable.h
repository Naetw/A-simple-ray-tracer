#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

class Ray;

class Hittable {
  public:
    /// Determine whether the passed-in ray hits the Hittable object
    virtual bool hit(const Ray &ray) const = 0;
};

#endif
