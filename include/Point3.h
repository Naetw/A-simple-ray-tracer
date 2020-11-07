#ifndef RAYTRACER_POINT3_H
#define RAYTRACER_POINT3_H

class Vector3;

/// This class stores a coordinate.
///
/// 3 stands for 3 dimensions. Take no account of homogeneous coordinate for simplicity.
class Point3 {
  private:
    double m_coordinate[3];

  public:
    ~Point3() = default;

    Point3() : m_coordinate{0, 0, 0} {}
    Point3(double x, double y, double z) : m_coordinate{x, y, z} {}

    double x() const { return m_coordinate[0]; }
    double y() const { return m_coordinate[1]; }
    double z() const { return m_coordinate[2]; }

};

Point3 operator+(const Point3 &point, const Vector3 &vec);
Point3 operator-(const Point3 &point, const Vector3 &vec);

Vector3 operator-(const Point3 &point1, const Point3 &point2);

#endif
