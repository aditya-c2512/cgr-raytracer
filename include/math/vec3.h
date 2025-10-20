//
// Created by Aditya Choubey on 19/09/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_VEC3_H
#define CGR_RAYTRACER_VEC3_H

#include <iostream>

class Vec3 {
private:
    double x, y, z;

public:
    // Initialisation
    Vec3();
    Vec3(double x, double y, double z);
    Vec3(const Vec3& v);

    // Getter functions
    double getX() const;
    double getY() const;
    double getZ() const;

    // Supported vector operations
    Vec3 operator - () const;
    Vec3 operator + (const Vec3& v) const;
    Vec3 operator - (const Vec3& v) const;
    Vec3 operator * (const Vec3& v) const;
    Vec3 operator / (const Vec3& v) const;
    Vec3 operator*(double length) const;
    Vec3 operator / (double length) const;
    Vec3& operator += (const Vec3& v);
    Vec3& operator *= (double t);
    Vec3& operator /= (double t);

    double length() const;
    double lengthSquared() const;

    double dot(const Vec3& v) const;
    Vec3 cross(const Vec3& v) const;
    Vec3 normalize() const;
};

inline std::ostream& operator << (std::ostream& os, const Vec3& v) {
    return os << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
}

using Point3 = Vec3;
#endif //CGR_RAYTRACER_VEC3_H