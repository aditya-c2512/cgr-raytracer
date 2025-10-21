//
// Created by Aditya Choubey on 20/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_PLANE_H
#define CGR_RAYTRACER_PLANE_H

#include <shapes/shape.h>
#include <utils/json/json_value.h>

class Plane: public Shape {
private:
    Logger* logger = Logger::getInstance();
    Point3 point;
    Vec3 normal;
    Point3 corners[4];

public:
    Plane(const Point3& point, const Vec3 &normal);
    explicit Plane(const JsonObject& shapeObject);

    bool intersect(const Ray &ray, double tMin, double tMax, Hit &record) override;
};

#endif //CGR_RAYTRACER_PLANE_H