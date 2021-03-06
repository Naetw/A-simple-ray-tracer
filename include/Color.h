#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "Vector3.h"

class Albedo;

/// This class stores colors (RGB) 
class Color {
  private:
    double m_pixel[3];

  public:
    ~Color() = default;

    Color() : m_pixel{0, 0, 0} {}
    Color(double r, double g, double b) : m_pixel{r, g, b} {}
    Color(const Vector3 &normal) {
        // FIXME: maybe use an abstract class which provides common behavior
        //        for Vector3, Color, Albedo
        // use unit vector for normalizing its range into 0.0 ~ 1.0
        const Vector3 &unit_vector = normal.getUnitVector();
        m_pixel[0] = unit_vector.x();
        m_pixel[1] = unit_vector.y();
        m_pixel[2] = unit_vector.z();
    }

    double r() const { return m_pixel[0]; }
    double g() const { return m_pixel[1]; }
    double b() const { return m_pixel[2]; }

    Color &operator+=(const Color &other_color);
};

Color operator+(const Color &color1, const Color &color2);
Color operator-(const Color &color1, const Color &color2);

Color operator*(const Albedo &attenuation, const Color &color);

#endif
