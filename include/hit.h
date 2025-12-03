//
// Created by Aditya Choubey on 14/11/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_HIT_H
#define CGR_RAYTRACER_HIT_H
#include "math/color.h"

class Material;

class Hit {
private:
    Point3 point;
    Vec3 normal;
    double t;
    Color color;
    bool isFrontFace{};
    bool textured{};
    double u, v;
    std::shared_ptr<Material> material;

public:
    Hit() : point(), normal(), t(0), color(), material(), isFrontFace(false) {}
    Hit(const Point3 &p, const Vec3 &n, const double t, const Color &col, std::shared_ptr<Material>& m, const bool isFrontFace):
        point(p), normal(n), t(t), color(col), material(m), isFrontFace(isFrontFace) {}

    void setPoint(const Point3 &p) { this->point = p; }
    void setNormal(const Vec3 &n) { this->normal = n; }
    void setT(double t) { this->t = t; }
    void setColor(const Color &c) { this->color = c; }
    void setMaterial(const std::shared_ptr<Material>& m) { this->material = m; }
    void setFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
        isFrontFace = ray.getDirection().dot(outwardNormal) < 0;
        normal = isFrontFace ? outwardNormal : -outwardNormal;
    }
    void setTextured(const bool isTextured) { this->textured = isTextured; }
    void setUV(const double u, const double v) { textured = true; this->u = u; this->v = v; }

    const Point3 &getPoint() const { return this->point; }
    const Vec3 &getNormal() const { return this->normal; }
    double getT() const { return this->t; }
    const Color &getColor() const { return this->color; }
    std::shared_ptr<Material>& getMaterial() { return this->material; }
    const bool& getIsFrontFace() const { return isFrontFace; }
    bool isTextured() const { return this->textured; }
    double getU() const { return this->u; }
    double getV() const { return this->v; }
};

#endif //CGR_RAYTRACER_HIT_H