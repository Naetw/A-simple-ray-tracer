#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H

#include "Material.h"

/// This class represents the Lambertian material which performs ideal diffuse
/// reflection
class Lambertian : public Material {
  public:
    ~Lambertian() = default;

    Lambertian() = default;
    Lambertian(const Albedo &albedo) : Material(albedo) {}

    virtual Ray getScatteredRay(const Ray &ray, const HitRecord &record) const override;
};

#endif
