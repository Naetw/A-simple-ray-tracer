#include "Point3.h"
#include "Vector3.h"

Point3 operator+(const Point3 &point, const Vector3 &vec) {
    return Point3(point.x() + vec.x(),
                  point.y() + vec.y(),
                  point.z() + vec.z());
}
Point3 operator-(const Point3 &point, const Vector3 &vec) {
    return Point3(point.x() - vec.x(),
                  point.y() - vec.y(),
                  point.z() - vec.z());
}

Vector3 operator-(const Point3 &point1, const Point3 &point2) {
    return Vector3(point1.x() - point2.x(),
                   point1.y() - point2.y(),
                   point1.z() - point2.z());
}
