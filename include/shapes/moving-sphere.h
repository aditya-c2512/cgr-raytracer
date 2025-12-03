//
// Created by Aditya Choubey on 01/12/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_MOVING_SPHERE_H
#define CGR_RAYTRACER_MOVING_SPHERE_H
#include "shape.h"

class MovingSphere: public Shape {
private:
    Logger* logger = Logger::getInstance();
    Vec3 startCenter, endCenter;
    double radius;
    std::shared_ptr<Material> material;

public:
    MovingSphere(const Vec3& startCenter, const Vec3& endCenter, double radius);
    explicit MovingSphere(const JsonObject &shapeObject);

    bool intersect(const Ray& ray, double tMin, double tMax, Hit& record) override;
};

#endif //CGR_RAYTRACER_MOVING_SPHERE_H