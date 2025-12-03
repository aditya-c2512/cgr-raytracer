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
    double time;

public:
    Ray();
    Ray(const Point3& origin, const Vec3& direction, double time = 0.0);

    Point3 getOrigin() const;
    Vec3 getDirection() const;
    double getTime() const;
    Point3 at(double t) const;

    std::string toString() const {
        return "Point: (" + std::to_string(origin.getX()) + ", " +
        std::to_string(origin.getY()) + ", " + std::to_string(origin.getZ()) + ") Direction: (" +
            std::to_string(direction.getX()) + ", " +
                std::to_string(direction.getY()) + ", " + std::to_string(direction.getZ()) + ")";
    }
    void visualise(const std::string& filename = "rays.txt") const;
};

#endif //CGR_RAYTRACER_RAY_H
