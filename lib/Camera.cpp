#include "Camera.h"
#include "Utility.h"

#include <cmath>

Camera::Camera(const Point3 &origin, const Point3 &look_at,
               const Vector3 &view_up, const double aspect_ratio,
               const double angle_of_vertical_field_of_view_in_degree,
               const double aperture, const double focus_distance,
               const uint32_t samples_per_pixel, const uint32_t max_depth)
    : m_origin(origin), m_lens_radius(aperture / 2),
      m_samples_per_pixel(samples_per_pixel), m_max_depth(max_depth) {
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

// FIXME: the logic of gamma-correct should be extracted as an independent function
static void writeColorToOstream(std::ostream &out, const Color &pixel_color,
                                const uint32_t samples_per_pixel) {
    double r = pixel_color.r();
    double g = pixel_color.g();
    double b = pixel_color.b();

    // divide the color by # of samples and gamma-correct for gamma=2.0
    auto scale = 1.0 / samples_per_pixel;
    auto gamma = 2.0;
    r = pow(scale * r, 1 / gamma);
    g = pow(scale * g, 1 / gamma);
    b = pow(scale * b, 1 / gamma);

    // write the translated [0,255] value of each color component.
    out << static_cast<uint32_t>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<uint32_t>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<uint32_t>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

void Camera::renderImageToOstream(const int32_t image_width,
                                  const int32_t image_height,
                                  const HittableList &world,
                                  std::ostream &out) const {
    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (auto j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rRemaining: " << j << ' ' << std::flush;
        Color pixel_color;

        for (int32_t i = 0; i < image_width; ++i) {
            // use multiple samples and random real numbers to blend the colors
            // of adjacent pixels, in this way, we can achieve simple
            // antialiasing
            for (uint32_t s = 0; s < m_samples_per_pixel; ++s) {
                auto u = (i + getRandomDouble01()) / (image_width - 1);
                auto v = (j + getRandomDouble01()) / (image_height - 1);
                const Ray &ray = getRay(u, v);
                pixel_color += ray.generateRayColor(world, m_max_depth);
            }
            writeColorToOstream(out, pixel_color, m_samples_per_pixel);
        }
    }
}
