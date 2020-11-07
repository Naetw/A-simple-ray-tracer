#include "Ray.h"

Point3 Ray::at(double factor) const {
    return m_origin + factor * m_direction;
}
