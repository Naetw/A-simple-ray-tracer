#include "Ray.h"

Point3 Ray::at(double factor) const {
    return m_origin + factor * m_direction;
}

bool Ray::operator!() const {
    return !(m_direction.squaredLength() != 0);
}
