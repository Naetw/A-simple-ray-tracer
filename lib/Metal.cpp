#include "Metal.h"
#include "Hittable.h"

Ray Metal::getScatteredRay(const Ray &ray, const HitRecord &record) const {
    // To get the refected vector, we just need to calculate the result
    // of a + 2b, where a is the vector of ray, b is the vector of the vector
    // component of a in normal vector (N) direction
    //
    // a      b
    //  \  N  ^                     ^^
    //   \ ^  |             a + 2b / | b
    //    v|  |                   /  |
    // ------------   ===>  ------------
    //                            \  ^
    //                           a \ | b
    //                              v|
    //
    //
    //
    // b can be calculated by -1 * dot(a, N) * N, where dot(a, N) can give us
    // the length of vector a in the reverse normal vector direction since the
    // angle between vector a and normal vector is larger than 90 degree
    const Vector3 &reflected_direction =
        ray.direction() +
        (-1 * 2 * dot(ray.direction(), record.normal) * record.normal);

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
