#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "Albedo.h"
#include "Ray.h"

class HitRecord;

/// Abstract base class for having different objects have different materials
class Material {
  private:
    Albedo m_albedo;

  public:
    ~Material() = default;

    Material() = default;
    Material(const Albedo &a) : m_albedo(a) {}

    const Albedo &getAlbedo() const { return m_albedo; }
    
    virtual Ray getScatteredRay(const Ray &ray, const HitRecord &record) const = 0;
};

#endif
