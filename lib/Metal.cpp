#include "Metal.h"
#include "Hittable.h"

Ray Metal::getScatteredRay(const Ray &ray, const HitRecord &record) const {
    const Vector3 &reflected_direction = Ray::getReflectedRay(ray, record.normal);

    // consider the fuzziness which causes a bit scatter
    const Vector3 &scattered_direction =
        reflected_direction +
        m_fuzziness * Vector3::getRandomVectorInUnitSphere();

    // catch the reflected vector that is pointing in the object
    if (dot(scattered_direction, record.normal) <= 0) {
        return Ray(record.point, Vector3(0, 0, 0));
    }

    return Ray(record.point, scattered_direction);
}
