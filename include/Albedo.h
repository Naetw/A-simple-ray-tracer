#ifndef RAYTRACER_ALBEDO_H
#define RAYTRACER_ALBEDO_H

#include "Vector3.h"

/// Normally, this should just be a single double.
/// This class extends it to have three different albedos on RGB which is more
/// flexible and can help generate more various image.
class Albedo {
  private:
    double m_components[3];

  public:
    ~Albedo() = default;

    Albedo() : m_components{0, 0, 0} {}
    Albedo(double r, double g, double b) : m_components{r, g, b} {}
    Albedo(double value) : m_components{value, value, value} {}
    Albedo(const Albedo &other) : m_components{other.r(), other.g(), other.b()} {}
    Albedo(const Vector3 &normal) {
        // FIXME: maybe use an abstract class which provides common behavior
        //        for Vector3, Color, Albedo
        // use unit vector for normalizing its range into 0.0 ~ 1.0
        // const Vector3 &unit_vector = normal.getUnitVector();
        const Vector3 &unit_vector = normal;
        m_components[0] = unit_vector.x();
        m_components[1] = unit_vector.y();
        m_components[2] = unit_vector.z();
    }

    double r() const { return m_components[0]; }
    double g() const { return m_components[1]; }
    double b() const { return m_components[2]; }
};

#endif
