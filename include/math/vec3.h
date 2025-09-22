//
// Created by Aditya Choubey on 19/09/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_VEC3_H
#define CGR_RAYTRACER_VEC3_H

class Vec3 {
private:
    double x, y, z;

public:
    // Initialisation
    Vec3(double x, double y, double z);
    Vec3(const Vec3& v);

    // Getter functions
    double getX() const;
    double getY() const;
    double getZ() const;

    // Supported vector operations
};

#endif //CGR_RAYTRACER_VEC3_H