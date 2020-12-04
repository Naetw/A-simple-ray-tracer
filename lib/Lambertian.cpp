#include "Lambertian.h"
#include "Hittable.h"

Ray Lambertian::getScatteredRay(const Ray &ray, const HitRecord &record) const {
    // diffuse reflection (Lambertian reflection) is achieved through
    // picking random points on the unit radius sphere tangent to the
    // hit point.
    const Vector3 &scatter_direction =
        record.normal + Vector3::getRandomVectorInUnitSphere();

    // catch degenerate scatter direction
    if (scatter_direction.nearZero()) {
        return Ray(record.point, record.normal);
    }

    return Ray(record.point, scatter_direction);
}
