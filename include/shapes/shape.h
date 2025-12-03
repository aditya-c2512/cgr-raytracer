//
// Created by Aditya Choubey on 07/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_SHAPE_H
#define CGR_RAYTRACER_SHAPE_H

#include <math/ray.h>

#include "hit.h"

class Shape {
private:

public:
    Shape() = default;
    virtual ~Shape() = default;

    virtual bool intersect(const Ray& ray, double tMin, double tMax, Hit& record) = 0;
};

#endif //CGR_RAYTRACER_SHAPE_H
