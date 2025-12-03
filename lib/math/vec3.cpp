//
// Created by Aditya Choubey on 19/09/2025.
//

#include <cmath>
#include <math/vec3.h>

#include "math/utils.h"

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

Vec3 Vec3::getRandom() {
    return { mathutils::getRandom(0,1), mathutils::getRandom(0,1), mathutils::getRandom(0,1)};
}

Vec3 Vec3::getRandom(double min, double max) {
    return { mathutils::getRandom(min, max), mathutils::getRandom(min, max), mathutils::getRandom(min, max)};
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
    if (this->lengthSquared() == 0) {
        return *this;
    }
    return (*this) / length();
}

Vec3 Vec3::reflect(const Vec3 &normal) const {
    return *this - normal * this->dot(normal) * 2;
}

Vec3 Vec3::refract(const Vec3& normal, double eta) const {
    const double cosTheta = std::min((-*this).dot(normal), 1.0);
    const Vec3 rOutPerp =  (*this + normal * cosTheta) * eta;
    const double k = 1.0 - rOutPerp.lengthSquared();

    if (k < 0) {
        return {0,0,0};
    }

    const Vec3 rOutParallel = normal * -std::sqrt(k);
    return rOutPerp + rOutParallel;
}
