#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Point3.h"
#include "Ray.h"
#include "Vector3.h"

#include <iostream>

class HittableList;

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

    uint32_t m_samples_per_pixel;
    uint32_t m_max_depth;

  public:
    ~Camera() = default;

    Camera(const Point3 &origin, const Point3 &look_at, const Vector3 &view_up,
           const double aspect_ratio,
           const double angle_of_vertical_field_of_view_in_degree,
           const double aperture, const double focus_distance,
           const uint32_t samples_per_pixel = 100, const uint32_t max_depth = 50);

    Ray getRay(double u, double v) const;

    /// Render the image to the specific output stream
    ///
    /// FIXME: extend this by specifying the image format in constructor
    void renderImageToOstream(const int32_t image_width,
                              const int32_t image_height,
                              const HittableList &world, std::ostream &out) const;
};

#endif
