#ifndef RAYTRACER_DIELECTRIC_H
#define RAYTRACER_DIELECTRIC_H

#include "Material.h"

/// This class represents the dielectric material which performs reflection or
/// refraction based on the refraction ratio of air and the material
class Dielectric : public Material {
  private:
    double m_refraction_index;

  public:
    ~Dielectric() = default;

    Dielectric() = default;

    Dielectric(double refraction_index)
        // Default albedo of dielectric material is 100%
        : Material(Albedo(1.0, 1.0, 1.0)), m_refraction_index(refraction_index) {}

    virtual Ray getScatteredRay(const Ray &ray, const HitRecord &record) const override;

  private:
    static double getReflectance(const double cosine, const double refraction_index);
};

#endif
