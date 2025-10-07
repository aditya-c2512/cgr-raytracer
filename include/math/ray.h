//
// Created by Aditya Choubey on 07/10/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_RAY_H
#define CGR_RAYTRACER_RAY_H
#include "vec3.h"

class Ray {
private:
    Point3 origin;
    Vec3 direction;
public:
    Ray();
    Ray(const Point3& origin, const Vec3& direction);

    Point3 getOrigin() const;
    Vec3 getDirection() const;
    Point3 at(double t) const;
};

#endif //CGR_RAYTRACER_RAY_H
