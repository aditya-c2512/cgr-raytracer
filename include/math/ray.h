//
// Created by Aditya Choubey on 07/10/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_RAY_H
#define CGR_RAYTRACER_RAY_H
#include "vec3.h"
#include "utils/logger.h"

class Ray {
private:
    Logger* logger = Logger::getInstance();

    Point3 origin;
    Vec3 direction;
public:
    Ray();
    Ray(const Point3& origin, const Vec3& direction);

    Point3 getOrigin() const;
    Vec3 getDirection() const;
    Point3 at(double t) const;

    void visualise(const std::string& filename = "rays.txt") const;
};

#endif //CGR_RAYTRACER_RAY_H
