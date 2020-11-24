#include "HittableList.h"
#include "Ray.h"

void HittableList::add(std::shared_ptr<Hittable> object) {
    m_objects.emplace_back(object);
}

HitRecord HittableList::getHitRecord(const Ray &ray, double t_min, double t_max) const {
    auto closest_so_far = t_max;
    HitRecord record;

    for (const auto &object : m_objects) {
        const HitRecord &tmp_record =
            object->getHitRecord(ray, t_min, closest_so_far);
        if (!tmp_record.point.isInfinity()) {
            closest_so_far = tmp_record.t;
            record = tmp_record;
        }
    }

    return record;
}
