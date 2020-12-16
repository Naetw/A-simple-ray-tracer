#include "Camera.h"
#include "Utility.h"

#include <cmath>

Camera::Camera(const Point3 &origin, const Point3 &look_at,
               const Vector3 &view_up, const double aspect_ratio,
               const double angle_of_vertical_field_of_view_in_degree,
               const double focal_length)
    : m_origin(origin) {
    /*
     *        /|
     *      /  | height
     *    / )  |
     *   o--N--> focal_length
     *    \ )
     *      \
     *        \
     *   o: origin point
     *   N: angle_of_vertical_field_of_view_in_degree
     */
    auto N = convertDegreeIntoRadian(angle_of_vertical_field_of_view_in_degree);
    auto height = tan(N / 2) * focal_length;
    auto viewport_height = 2 * height;
    auto viewport_width = aspect_ratio * viewport_height;

    // get x, y, z axes of the camera instead of
    // the normal ones (1, 0, 0), (0, 1, 0), (0, 0, 1)
    auto z_axis = (origin - look_at).getUnitVector();
    auto x_axis = cross(view_up, z_axis).getUnitVector();
    auto y_axis = cross(z_axis, x_axis);

    m_vertical = viewport_height * y_axis;
    m_horizontal = viewport_width * x_axis;
    m_lower_left_corner =
        origin - (m_vertical / 2) - (m_horizontal / 2) - focal_length * z_axis ;
}
