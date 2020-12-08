#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "Material.h"

/// This class represents the metal material which can reflects almost all
/// wavelengths of visible ray when it's smooth enough.
class Metal : public Material {
  private:
    /// Define the fuzziness (smoothness) of the metal which causes scatter
    double m_fuzziness;

  public:
    ~Metal() = default;

    Metal() = default;
    Metal(const Albedo &albedo, double fuzziness)
        : Material(albedo), m_fuzziness(fuzziness < 1 ? fuzziness : 1) {}

    virtual Ray getScatteredRay(const Ray &ray, const HitRecord &record) const override;
};

#endif
