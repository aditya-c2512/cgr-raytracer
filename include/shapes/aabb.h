//
// Created by Aditya Choubey on 25/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_AABB_H
#define CGR_RAYTRACER_AABB_H

#include <shapes/shape.h>
#include <utils/json/json_value.h>

class AxisAlignedBBox: public Shape {
private:
    Vec3 minPoint, maxPoint;

public:
    AxisAlignedBBox() = default;
    AxisAlignedBBox(const Vec3 &minPoint, const Vec3 &maxPoint);
    AxisAlignedBBox(const JsonObject &shapeObject);

    bool intersect(const Ray &ray, double tMin, double tMax, Hit &record) override;
};

#endif //CGR_RAYTRACER_AABB_H
