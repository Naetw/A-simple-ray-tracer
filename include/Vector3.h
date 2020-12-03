#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

/// This class stores geometric vectors and provides common operations of it,
/// such as dot product.
/// 
/// 3 stands for 3 dimensions. Take no account of homogeneous coordinate for simplicity.
class Vector3 {
  private:
    double m_components[3];

  public:
    ~Vector3() = default;

    Vector3() : m_components{0, 0, 0} {}
    Vector3(double x, double y, double z) : m_components{x, y, z} {}
    Vector3(double factor) : m_components{factor, factor, factor} {}
    Vector3(const Vector3 &other) : m_components{other.x(), other.y(), other.z()} {}

    double x() const { return m_components[0]; }
    double y() const { return m_components[1]; }
    double z() const { return m_components[2]; }

    /// Return a Vector3 that all components are in range [0, 1]
    static Vector3 getRandomVector();
    static Vector3 getRandomUnitVector();

    double length() const;

    Vector3 getUnitVector() const;

    Vector3 operator-() const;
};

/// Used for scalar multiplication
/// Warning: this isn't the dot product
Vector3 operator*(const Vector3 &factor, const Vector3 &vec);

Vector3 operator/(const Vector3 &vec, const Vector3 &divisor);

double dot(const Vector3 &u, const Vector3 &v);

#endif
