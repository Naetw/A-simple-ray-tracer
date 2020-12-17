#include "Vector3.h"
#include "Utility.h"

#include <cmath>

Vector3 Vector3::getRandomVector() {
    return Vector3(getRandomDouble01(),
                   getRandomDouble01(),
                   getRandomDouble01());
}

Vector3 Vector3::getRandomVector(double min, double max) {
    return Vector3(getRandomDoubleInRange(min, max),
                   getRandomDoubleInRange(min, max),
                   getRandomDoubleInRange(min, max));
}

Vector3 Vector3::getRandomVectorInUnitSphere() {
    while (true) {
        auto v = getRandomVector(-1, 1);
        if (v.squaredLength() >= 1) {
            continue;
        }
        return v;
    }
}

Vector3 Vector3::getRandomVectorInUnitDisk() {
    while (true) {
        auto v = Vector3(getRandomDoubleInRange(-1, 1),
                         getRandomDoubleInRange(-1, 1),
                         0);
        if (v.squaredLength() >= 1) {
            continue;
        }
        return v;
    }
}

double Vector3::squaredLength() const { return dot(*this, *this); }

// FIXME: see if this can only be calculated once
double Vector3::length() const { return sqrt(squaredLength()); }

// FIXME: see if this can only be calculated once
Vector3 Vector3::getUnitVector() const { return *this / length(); }

bool Vector3::nearZero() const {
    const auto threshold = 1e-8;
    return (fabs(m_components[0]) < threshold) &&
           (fabs(m_components[1]) < threshold) &&
           (fabs(m_components[2]) < threshold);
}

Vector3 Vector3::operator-() const {
    return Vector3(-m_components[0], -m_components[1], -m_components[2]);
}

Vector3 operator+(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.x() + v2.x(),
                   v1.y() + v2.y(),
                   v1.z() + v2.z());
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

Vector3 cross(const Vector3 &u, const Vector3 &v) {
    return Vector3(u.y() * v.z() - u.z() * v.y(),
                   u.z() * v.x() - u.x() * v.z(),
                   u.x() * v.y() - u.y() * v.x());
}
