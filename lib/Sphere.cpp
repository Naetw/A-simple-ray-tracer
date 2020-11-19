#include "Sphere.h"
#include "Ray.h"
#include "Vector3.h"

/// A sphere centered at the origin of radius R is x^2 + y^2 + z^2 = R^2
///
/// We can easily calculate whether a ray hits a sphere by applying the
/// end point of the ray (x, y, z) in the equation of sphere:
///     If (x, y, z) is inside the sphere: x^2 + y^2 + z^2 < R^2
///     If (x, y, z) is outside the sphere: x^2 + y^2 + z^2 > R^2
///     If (x, y, z) is on the sphere: x^2 + y^2 + z^2 = R^2
///
/// However, a sphere may be centered at a random point C (Cx, Cy, Cz)
/// and a ray is extensible: origin (O) + t * direction (d) where t is a
/// dynamic factor. If we take these situations into account, the equation
/// would be (O + td - C) dot (O + td - C) >/=/< R^2 (remember that the sum
/// of squares can be formed in terms of the dot product of vectors) which
/// can be further formatted into:
///     t^2 * d dot d + 2t * d dot (O - C) + (O - C) dot (O - C) - R^2 = 0
/// Note that there's only one variable - t in the above equation, others
/// are just constant which means that the equation is just a quadratic equation
///
/// This method calculates the discriminant (b^2 - 4ac) according to
/// passed-in Ray
double Sphere::calculateDiscriminant(const Ray& ray) const {
    Vector3 origin_to_center(ray.origin() - m_center);
    auto a = dot(ray.direction(), ray.direction());
    auto b = 2.0 * dot(ray.direction(), origin_to_center);
    auto c = dot(origin_to_center, origin_to_center) - m_radius * m_radius;
    return (b * b) - (4 * a * c);
}

/// We can just use the formula: b^2 - 4ac to determine whether
/// there's a hit
bool Sphere::hit(const Ray& ray) const {
    auto discriminant = calculateDiscriminant(ray);
    return discriminant >= 0;
}
