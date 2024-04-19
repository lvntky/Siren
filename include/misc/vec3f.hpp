/*
* Influenced from java.lang.Object.jpview.graphics.Vec3f 
* The Vec3f class provides a vector object for 3 dimensional locations or RGB pixel values.
* The class offers static methods for standard vector operations.
*/
#ifndef VEC3F_HPP_
#define VEC3F_HPP_

#include <cmath>

class Vec3f {
public:
    float x, y, z;
    float raw[3]; 

    Vec3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x(_x), y(_y), z(_z) {}

    // Vector addition
    Vec3f operator+(const Vec3f& other) const {
        return Vec3f(x + other.x, y + other.y, z + other.z);
    }

    // Vector subtraction
    Vec3f operator-(const Vec3f& other) const {
        return Vec3f(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    Vec3f operator*(float scalar) const {
        return Vec3f(x * scalar, y * scalar, z * scalar);
    }

    // Cross product
    Vec3f cross(const Vec3f& other) const {
        return Vec3f(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Dot product
    float dot(const Vec3f& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Length (magnitude) of the vector
    float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    // Normalize the vector
    Vec3f normalize() const {
        float len = length();
        if (len != 0) {
            return Vec3f(x / len, y / len, z / len);
        }
        return *this; // return the zero vector
    }
};

#endif //VEC3F_HPP_