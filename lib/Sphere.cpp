#include "Sphere.h"
#include "Ray.h"
#include "Utility.h"
#include "Vector3.h"

#include <cmath>
#include <utility>

struct QuadraticFactor {
    double a;
    double b;
    double c;
};

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
static QuadraticFactor calculateQuadraticFactors(const Sphere &sphere,
                                                 const Ray &ray) {
    Vector3 origin_to_center(ray.origin() - sphere.center());
    QuadraticFactor factors;
    factors.a = dot(ray.direction(), ray.direction());
    factors.b = 2.0 * dot(ray.direction(), origin_to_center);
    factors.c = dot(origin_to_center, origin_to_center) -
                sphere.radius() * sphere.radius();
    return factors;
}

/// This method calculates the discriminant (b^2 - 4ac) according to
/// passed-in Ray
static double calculateDiscriminant(const QuadraticFactor &factors) {
    return (factors.b * factors.b) - (4 * factors.a * factors.c);
}

static double calculateDiscriminant(const Sphere &sphere, const Ray &ray) {
    QuadraticFactor factors = calculateQuadraticFactors(sphere, ray);
    return calculateDiscriminant(factors);
}

static bool isHit(double discriminant) { return discriminant >= 0; }

/// We can just use the formula: b^2 - 4ac to determine whether
/// there's a hit
bool Sphere::hit(const Ray &ray) const {
    auto discriminant = calculateDiscriminant(*this, ray);
    return isHit(discriminant);
}

HitRecord Sphere::getHitRecord(const Ray &ray, double t_min,
                               double t_max) const {
    auto factors = calculateQuadraticFactors(*this, ray);
    auto discriminant = calculateDiscriminant(factors);

    // Wrong direction, no way to hit
    if (!isHit(discriminant)) {
        return HitRecord();
    }

    auto sqrt_discriminant = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    auto root = (-factors.b - sqrt_discriminant) / (2 * factors.a);
    if (root < t_min || t_max < root) {
        root = (-factors.b + sqrt_discriminant) / (2 * factors.a);
        if (root < t_min || t_max < root) {
            return HitRecord();
        }
    }

    const Point3 &intersection_point = ray.at(root);
    const Vector3 &outward_normal = (intersection_point - m_center) / m_radius;
    HitRecord record(intersection_point, root, getMaterialPointer());
    record.setFaceNormalVector(ray, outward_normal);

    return record;
}
