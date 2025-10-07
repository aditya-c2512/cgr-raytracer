//
// Created by Aditya Choubey on 07/10/2025.
//

#include <math/ray.h>

Ray::Ray(): origin(0, 0, 0), direction(0, 0, 0) {
}

Ray::Ray(const Point3 &origin, const Vec3 &direction): origin(origin), direction(direction) {
}

Point3 Ray::getOrigin() const {
    return origin;
}

Vec3 Ray::getDirection() const {
    return direction;
}

Point3 Ray::at(const double t) const {
    return origin + direction * t;
}