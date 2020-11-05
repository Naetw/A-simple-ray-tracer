#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <cstdint>
#include <iostream>

/// This class stores colors (RGB) 
class Color {
  private:
    double m_pixel[3];

  public:
    ~Color() = default;

    Color() : m_pixel{0, 0, 0} {}
    Color(double r, double g, double b) : m_pixel{r, g, b} {}

    double r() const { return m_pixel[0]; }
    double g() const { return m_pixel[1]; }
    double b() const { return m_pixel[2]; }
};

void writeColorToStream(std::ostream &out, const Color &pixel_color);

#endif
