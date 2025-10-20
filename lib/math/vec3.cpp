//
// Created by Aditya Choubey on 19/09/2025.
//

#include <cmath>
#include <math/vec3.h>

Vec3::Vec3(): x(0), y(0), z(0) {}

Vec3::Vec3(double x, double y, double z): x(x), y(y), z(z) {}

Vec3::Vec3(const Vec3 &v): x(v.x), y(v.y), z(v.z) {}

double Vec3::getX() const {
    return x;
}

double Vec3::getY() const {
    return y;
}

double Vec3::getZ() const {
    return z;
}

Vec3 Vec3::operator-() const {
    return {-x, -y, -z};
}

Vec3 Vec3::operator+(const Vec3 &v) const {
    return {x + v.x, y + v.y, z + v.z};
}

Vec3 Vec3::operator-(const Vec3 &v) const {
    return {x - v.x, y - v.y, z - v.z};
}

Vec3 Vec3::operator*(const Vec3 &v) const {
    return {x * v.x, y * v.y, z * v.z};
}

Vec3 Vec3::operator/(const Vec3 &v) const {
    return {x / v.x, y / v.y, z / v.z};
}

Vec3 Vec3::operator*(double length) const {
    return {x * length, y * length, z * length};
}

Vec3 Vec3::operator/(double length) const {
    return {x / length, y / length, z / length};
}

Vec3 & Vec3::operator+=(const Vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3 & Vec3::operator*=(double t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

Vec3 & Vec3::operator/=(double t) {
    x /= t;
    y /= t;
    z /= t;
    return *this;
}

double Vec3::length() const {
    return std::sqrt(lengthSquared());
}

double Vec3::lengthSquared() const {
    return x * x + y * y + z * z;
}

double Vec3::dot(const Vec3 &v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vec3 Vec3::cross(const Vec3 &v) const {
    return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

Vec3 Vec3::normalize() const {
    return (*this) / length();
}
