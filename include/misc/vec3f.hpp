#ifndef VEC3F_HPP
#define VEC3F_HPP

#include <cmath>

class Vec3f {
public:
    float x, y, z;

    // Constructors
    Vec3f() : x(0.0f), y(0.0f), z(0.0f) {}
    Vec3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    // Copy constructor
    Vec3f(const Vec3f& other) : x(other.x), y(other.y), z(other.z) {}

    // Assignment operator
    Vec3f& operator=(const Vec3f& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    // Access operators
    float& operator[](int index) {
        if (index == 0) return x;
        else if (index == 1) return y;
        else return z;
    }

    const float& operator[](int index) const {
        if (index == 0) return x;
        else if (index == 1) return y;
        else return z;
    }

    // Addition operator
    Vec3f operator+(const Vec3f& other) const {
        return Vec3f(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction operator
    Vec3f operator-(const Vec3f& other) const {
        return Vec3f(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    Vec3f operator*(float scalar) const {
        return Vec3f(x * scalar, y * scalar, z * scalar);
    }

    // Dot product
    float dot(const Vec3f& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vec3f cross(const Vec3f& other) const {
        return Vec3f(y * other.z - z * other.y,
                     z * other.x - x * other.z,
                     x * other.y - y * other.x);
    }

    // Length of the vector
    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalize the vector
    Vec3f normalize() const {
        float len = length();
        if (len != 0)
            return Vec3f(x / len, y / len, z / len);
        else
            return *this;
    }
};

#endif // VEC3F_HPP