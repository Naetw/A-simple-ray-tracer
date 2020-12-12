#include "Dielectric.h"
#include "Hittable.h"
#include "Utility.h"

#include <cmath>

Ray Dielectric::getScatteredRay(const Ray &ray, const HitRecord &record) const {
    // Refraction is described by Snell's law:
    //     eta dot sin(theta) = eta' dot sin(theta')
    // refraction_ratio is eta / eta' where eta is the refraction_index of
    // 'from' and eta' is the refraction_index of 'to'
    //
    // Default material outside *this is air and it's refraction index is 1.0
    // TODO: replace 1.0 with maybe a data member
    double refraction_ratio =
        record.front_face ? (1.0 / m_refraction_index) : m_refraction_index;

    // -1 since the angle between ray direction & normal is larger than 90
    // degree
    double cosine_theta = fmin(-1 * dot(ray.direction().getUnitVector(), record.normal), 1);
    double sine_theta = sqrt(1 - cosine_theta * cosine_theta);

    if (refraction_ratio * sine_theta > 1 ||
        getReflectance(cosine_theta, m_refraction_index) > getRandomDouble01()) {
        // must reflect when the total internal reflection happens or
        // the ray points in a steep angle which makes a dielectric material act like a mirror
        return Ray(record.point, Ray::getReflectedRay(ray, record.normal));
    } else {
        // can refract
        return Ray(record.point, Ray::getRefractedRay(ray, record.normal, refraction_ratio));
    }
}

double Dielectric::getReflectance(const double cosine, const double refraction_index) {
    // use Schlick's approximation
    // r0 = (n1 - n2) / (n1 + n2) where n1, n2 are the indices of refraction of
    // the two material (n1 is default to 1 since it's air)
    // TODO: replace n1 with maybe a data member
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
