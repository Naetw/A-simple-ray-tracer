#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Point3.h"
#include "Ray.h"
#include "Vector3.h"

/// This class describes a virtual camera which can be thought as a source of
/// laser beam. It contains following attributes:
///
/// - origin: a center point of the camera
/// - horizontal, vertical: vectors that form the rectangle of the viewport
/// - lower_left_corner: lower left corner of the viewport
///
/// Viewport is a 2D rectangle used to project the 3D scene to the position of
/// a virtual camera.
///
/// lower_left_corner is used for generating the ray of camera (a reverse
/// direction of the ray from viewport to origin).
class Camera {
  private:
    const Point3 m_origin;
    const Vector3 m_horizontal;
    const Vector3 m_vertical;
    const Point3 m_lower_left_corner;

  public:
    ~Camera() = default;

    Camera(const Point3 &origin, double aspect_ratio, double viewport_height,
           double focal_length)
        : m_origin(origin),
          m_horizontal(/* viewport_width */ aspect_ratio * viewport_height, 0,
                       0),
          m_vertical(0, viewport_height, 0),
          // origin - (0, 0, focal_length) == center of the viewport
          m_lower_left_corner(m_origin - m_horizontal / 2 - m_vertical / 2 -
                              Vector3(0, 0, focal_length)) {}

    Ray getRay(double u, double v) const {
        return Ray(m_origin, m_lower_left_corner + u * m_horizontal +
                                 v * m_vertical - m_origin);
    }
};

#endif
