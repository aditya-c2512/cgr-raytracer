//
// Created by Aditya Choubey on 20/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_CUBE_H
#define CGR_RAYTRACER_CUBE_H

#include <shapes/shape.h>
#include <utils/json/json_value.h>

#include "materials/blinn-phong-material.h"

class Cube: public Shape {
private:
    Point3 minPoint, maxPoint;
    std::shared_ptr<Material> material;

public:
    Cube(const Point3 &min, const Point3 &max);
    explicit Cube(const JsonObject& shapeObject);

    bool intersect(const Ray &ray, double tMin, double tMax, Hit &record) override;
};

#endif //CGR_RAYTRACER_CUBE_H