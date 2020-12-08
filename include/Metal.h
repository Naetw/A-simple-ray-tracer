#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "Material.h"

/// This class represents the metal material which just reflects the ray
/// instead of causing the ray scatter
class Metal : public Material {
  public:
    ~Metal() = default;

    Metal() = default;
    Metal(const Albedo &albedo) : Material(albedo) {}

    virtual Ray getScatteredRay(const Ray &ray, const HitRecord &record) const override;
};

#endif
