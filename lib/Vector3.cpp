#include "Vector3.h"

#include <math.h>

// FIXME: see if this can only be calculated once
double Vector3::length() const {
    return sqrt(dot(*this, *this));
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

double dot(const Vector3 &u, const Vector3 &v) {
    return u.x() * v.x() +
           u.y() * v.y() +
           u.z() * v.z();
}