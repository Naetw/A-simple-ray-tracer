#include "Dielectric.h"
#include "Hittable.h"

#include <cmath>

Ray Dielectric::getScatteredRay(const Ray &ray, const HitRecord &record) const {
    // Refraction is described by Snell's law:
    //     eta dot sin(theta) = eta' dot sin(theta')
    // refraction_ratio is eta / eta' where eta is the refraction_index of
    // 'from' and eta' is the refraction_index of 'to'
    //
    // Default material outside *this is air and it's refraction index is 1.0
    double refraction_ratio =
        record.front_face ? (1.0 / m_refraction_index) : m_refraction_index;

    // -1 since the angle between ray direction & normal is larger than 90
    // degree
    double cosine_theta = fmin(-1 * dot(ray.direction().getUnitVector(), record.normal), 1);
    double sine_theta = sqrt(1 - cosine_theta * cosine_theta);

    if (refraction_ratio * sine_theta > 1) {
        // must reflect when the total internal reflection happens
        return Ray(record.point, Ray::getReflectedRay(ray, record.normal));
    } else {
        // can refract
        return Ray(record.point, Ray::getRefractedRay(ray, record.normal, refraction_ratio));
    }
}
