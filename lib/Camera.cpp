#include "Camera.h"
#include "Utility.h"

#include <cmath>

Camera::Camera(const Point3 &origin, const Point3 &look_at,
               const Vector3 &view_up, const double aspect_ratio,
               const double angle_of_vertical_field_of_view_in_degree,
               const double aperture, const double focus_distance)
    : m_origin(origin), m_lens_radius(aperture / 2) {
    /*
     *        /|
     *      /  | height
     *    / )  |
     *   o--N--> focal_length (focus_distance)
     *    \ )
     *      \
     *        \
     *   o: origin
     *   N: angle_of_vertical_field_of_view_in_degree
     *
     * For a real camera, there're two parts that we need simulate which is
     * too complicated. With the thin lens approximation, we know that rays from
     * a slice away from the thin lens will focus on the same slice (plane) on
     * the other side of the lens. Since we render the image outside the
     * camera, we can just place the image plane at the focus plane.
     */
    auto N = convertDegreeIntoRadian(angle_of_vertical_field_of_view_in_degree);
    auto height = tan(N / 2) * focus_distance;
    auto viewport_height = 2 * height;
    auto viewport_width = aspect_ratio * viewport_height;

    // get x, y, z axes of the camera instead of
    // the normal ones (1, 0, 0), (0, 1, 0), (0, 0, 1)
    m_z_axis = (origin - look_at).getUnitVector();
    m_x_axis = cross(view_up, m_z_axis).getUnitVector();
    m_y_axis = cross(m_z_axis, m_x_axis);

    m_vertical = viewport_height * m_y_axis;
    m_horizontal = viewport_width * m_x_axis;
    m_lower_left_corner = origin - (m_vertical / 2) - (m_horizontal / 2) -
                          focus_distance * m_z_axis;
}

Ray Camera::getRay(double u, double v) const {
    /*
     * Add the effect of defocus blur (depth of field) when m_lens_radius is not
     * 0
     *
     * The reason why defocus blur (depth of field) can be achieved by adding an
     * offset on m_origin is that the focus plane has been fixed on a specific
     * distance and having any point other than m_origin as the origin of a ray
     * will result in a different ray direction and that will result in a
     * different color compared to a ray originated at m_origin. The combination
     * of different colors results in a blurry effect.
     *
     *  o'                    |
     *   \                    |
     *    ------------------  |
     *                      \ |
     *  o-------------------->p (look_at)
     *      focus distance    |
     *                        |
     *
     *  o: origin
     *  o': any point other than origin
     *  p: look_at point
     *
     * With a fixed aperture, the farther the focus plane (deep depth of field)
     * is, the more objects can be sharp enough since more objects can be
     * located in the triangle clamped by vector o'p and vector op, which is
     * small enough that vector o'p won't point to a point with different color.
     * Ref:
     * https://physicssoup.wordpress.com/2012/05/18/why-does-a-small-aperture-increase-depth-of-field/
     *
     * The effect of close focus plane (shallow depth of field) or different
     * apertures can be deduced using the same manner.
     */
    const Vector3 &radius_vector =
        m_lens_radius * Vector3::getRandomVectorInUnitDisk();
    // apply the offset on the coordinate system of the camera
    const Vector3 &offset =
        m_x_axis * radius_vector.x() + m_y_axis * radius_vector.y();

    const Point3 &new_origin = m_origin + offset;
    return Ray(new_origin, m_lower_left_corner + u * m_horizontal +
                               v * m_vertical - new_origin);
}
