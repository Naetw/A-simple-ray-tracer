#include "Ray.h"
#include "HittableList.h"
#include "Material.h"

#include <cmath>

Point3 Ray::at(double factor) const { return m_origin + factor * m_direction; }

Color Ray::generateRayColor(
    const HittableList &world, uint32_t depth,
    std::function<Color(const Ray &)> generateBackgroundColor) const {
    if (depth == 0) {
        // if we've exceeded the ray bounce limit, no more light is gathered.
        return /* black */ Color(0, 0, 0);
    }

    // 0.001 for ignoring the hits that the `t` is very close to 0
    const HitRecord &record = world.getHitRecord(*this, 0.001, kInfinity);
    if (!record.point.isInfinity()) {
        const Ray &scattered_ray =
            record.material_ptr->getScatteredRay(*this, record);
        if (!scattered_ray) {
            // all rays have been absorbed
            return /* black */ Color(0, 0, 0);
        }
        // attenuation determines how much is the proportion of ray being
        // reflected
        const Albedo &attenuation = record.material_ptr->getAlbedo();
        return attenuation * scattered_ray.generateRayColor(
                                 world, depth - 1, generateBackgroundColor);
    }

    //
    // background
    //
    return generateBackgroundColor(*this);
}

bool Ray::operator!() const { return !(m_direction.squaredLength() != 0); }

/// To get the reflected vector, we just need to calculate the result
/// of a + 2b, where a is the vector of ray, b is the vector of the vector
/// component of a in normal vector (N) direction
///
/// a      b
///  \  N  ^                     ^^
///   \ ^  |             a + 2b / | b
///    v|  |                   /  |
/// ------------   ===>  ------------
///                            \  ^
///                           a \ | b
///                              v|
///
///
///
/// b can be calculated by -1 * dot(a, N) * N, where dot(a, N) can give us
/// the length of vector a in the reverse normal vector direction since the
/// angle between vector a and normal vector is larger than 90 degree
Vector3 Ray::getReflectedRay(const Ray &ray, const Vector3 &normal) {
    return ray.direction() + (-1 * 2 * dot(ray.direction(), normal) * normal);
}

/// Refracted vector can be calculated by adding the perpendicular part and
/// the parallel part. The formulas for these two parts can be deduced
/// through Snell's law.
Vector3 Ray::getRefractedRay(const Ray &ray, const Vector3 &normal,
                             double refraction_ratio) {
    const Vector3 &ray_unit_direction = ray.direction().getUnitVector();
    // -1 since the angle between ray direction & normal is larger than 90
    // degree
    double cosine_theta = fmin(-1 * dot(ray_unit_direction, normal), 1);
    const Vector3 &refracted_direction_perp =
        refraction_ratio * (ray_unit_direction + cosine_theta * normal);
    const Vector3 &refracted_direction_parallel =
        -1 * sqrt(1 - fabs(refracted_direction_perp.squaredLength())) * normal;

    return refracted_direction_perp + refracted_direction_parallel;
}
