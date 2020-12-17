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
    Point3 m_origin;

    // vertical, horizontal, lower_left_corner MUST be adjusted if the origin
    // was modified
    Vector3 m_vertical;
    Vector3 m_horizontal;
    Point3 m_lower_left_corner;

    // x_axis, y_axis, z_axis MUST be adjusted if the origin
    // was modified
    Vector3 m_x_axis;
    Vector3 m_y_axis;
    Vector3 m_z_axis;

    double m_lens_radius;

  public:
    ~Camera() = default;

    Camera(const Point3 &origin, const Point3 &look_at, const Vector3 &view_up,
           const double aspect_ratio,
           const double angle_of_vertical_field_of_view_in_degree,
           const double aperture, const double focus_distance);

    Ray getRay(double u, double v) const;
};

#endif
