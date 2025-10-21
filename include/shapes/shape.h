//
// Created by Aditya Choubey on 07/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_SHAPE_H
#define CGR_RAYTRACER_SHAPE_H

#include <math/ray.h>

#include "math/color.h"

class Hit {
private:
    Point3 point;
    Vec3 normal;
    double t;
    Color color;

public:
    Hit(): point(), normal(), t(0), color(Color(0, 0, 0)) {}
    Hit(const Point3 &p, const Vec3 &n, double t, Color col): point(p), normal(n), t(t), color(col) {}

    void setPoint(const Point3 &p) { this->point = p; }
    void setNormal(const Vec3 &n) { this->normal = n; }
    void setT(double t) { this->t = t; }
    void setColor(const Color &c) { this->color = c; }

    const Point3 &getPoint() const { return this->point; }
    const Vec3 &getNormal() const { return this->normal; }
    double getT() const { return this->t; }
    const Color &getColor() const { return this->color; }
};

class Shape {
private:

public:
    Shape() = default;
    virtual ~Shape() = default;

    virtual bool intersect(const Ray& ray, double tMin, double tMax, Hit& record) = 0;
};

#endif //CGR_RAYTRACER_SHAPE_H
