#include "Vector3.h"

#include <math.h>

// FIXME: see if this can only be calculated once
double Vector3::length() const {
    return sqrt(m_components[0] * m_components[0] +
                m_components[1] * m_components[1] +
                m_components[2] * m_components[2]);
}

// FIXME: see if this can only be calculated once
Vector3 Vector3::getUnitVector() const {
    return *this / length();
}

Vector3 operator*(const Vector3 &factor, const Vector3 &vec) {
    return Vector3(factor.x() * vec.x(),
                   factor.y() * vec.y(),
                   factor.z() * vec.z());
}

Vector3 operator/(const Vector3 &vec, const Vector3 &divisor) {
    return Vector3(vec.x() / divisor.x(),
                   vec.y() / divisor.y(),
                   vec.z() / divisor.z());
}
