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

    static Vec3 getRandom();
    static Vec3 getRandom(double min, double max);
    static Vec3 getRandomUnitVector() {
        while (true) {
            auto p = getRandom(-1,1);
            if (1e-160 < p.lengthSquared() && p.lengthSquared() <= 1)
                return p / sqrt(p.lengthSquared());
        }
    }
    static Vec3 getRandomUnitVectorOnHemisphere(const Vec3& normal) {
        auto vec = getRandomUnitVector();
        if (vec.dot(normal) > 0) {
            return vec;
        }
        return -vec;
    }

    bool isNearZero() const {
        constexpr auto error = 1e-8;
        return (std::fabs(x) < error) && (std::fabs(y) < error) && (std::fabs(z) < error);
    }

    double& operator[](const int i) {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default:
                throw std::out_of_range("Vec3 index out of range (valid: 0, 1, 2)");
        }
    }

    const double& operator[](const int i) const {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default:
                throw std::out_of_range("Vec3 index out of range (valid: 0, 1, 2)");
        }
    }

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
    Vec3 reflect(const Vec3& normal) const;
    Vec3 refract(const Vec3& normal, double refractionIndex) const;
};

inline std::ostream& operator << (std::ostream& os, const Vec3& v) {
    return os << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
}

using Point3 = Vec3;
#endif //CGR_RAYTRACER_VEC3_H