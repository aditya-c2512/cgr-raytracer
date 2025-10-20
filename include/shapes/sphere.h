//
// Created by Aditya Choubey on 13/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_SPHERE_H
#define CGR_RAYTRACER_SPHERE_H

#include <shapes/shape.h>
#include <utils/json/json_value.h>

class Sphere: public Shape {
private:
    Vec3 center;
    double radius;

public:
    Sphere(const Vec3& center, double radius);
    explicit Sphere(const JsonObject &shapeObject);

    bool intersect(const Ray& ray, double tMin, double tMax, Hit& record) override;
};

#endif //CGR_RAYTRACER_SPHERE_H