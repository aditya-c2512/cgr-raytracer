//
// Created by Aditya Choubey on 20/10/2025.
//
#include <shapes/plane.h>

#include "materials/blinn-phong-material.h"

Plane::Plane(const Point3 &point, const Vec3 &normal): point(point), normal(normal) {
}

Plane::Plane(const JsonObject &shapeObject) {
    auto normalArray = shapeObject.at("normal").as<JsonArray>();
    auto pointArray = shapeObject.at("point").as<JsonArray>();

    normal = Vec3(normalArray[0].as<double>(), normalArray[1].as<double>(), normalArray[2].as<double>());
    point = Point3(pointArray[0].as<double>(), pointArray[1].as<double>(), pointArray[2].as<double>());

    auto materialObject = shapeObject.at("material").as<JsonObject>();
    material = std::make_shared<BlinnPhongMaterial>(materialObject);
}

bool Plane::intersect(const Ray &ray, double tMin, double tMax, Hit &record) {
    double denom = ray.getDirection().dot(normal);
    if (std::fabs(denom) < 1e-8)
        return false;

    double t = (point - ray.getOrigin()).dot(normal) / denom;
    if (t < tMin || t > tMax)
        return false;

    Point3 hitPoint = ray.getOrigin() + ray.getDirection() * t;

    if (!isInside(hitPoint))
        return false;

    record.setT(t);
    record.setPoint(hitPoint);
    record.setFaceNormal(ray, normal);
    record.setMaterial(material);
    record.setUV(hitPoint.getX() / (TX - 1), hitPoint.getY() / (TY - 1));

    return true;
}

bool Plane::isInside(const Point3 &p) const {
    for (int i = 0; i < 4; ++i) {
        const Point3 &a = corners[i];
        const Point3 &b = corners[(i + 1) % 4];
        Vec3 edge = b - a;
        Vec3 toPoint = p - a;
        Vec3 crossProd = edge.cross(toPoint);

        if (crossProd.dot(normal) < 0)
            return false;
    }
    return true;
}