//
// Created by Aditya Choubey on 13/10/2025.
//
#include <shapes/sphere.h>

#include "materials/blinn-phong-material.h"

Sphere::Sphere(const Vec3& center, const double radius): center(center), radius(radius) {
}

Sphere::Sphere(const JsonObject &shapeObject) {
    const auto centerArray = shapeObject.at("location").as<JsonArray>();
    center = Vec3(centerArray[0].as<double>(), centerArray[1].as<double>(), centerArray[2].as<double>());
    radius = shapeObject.at("radius").as<double>() * 1;

    auto materialObject = shapeObject.at("material").as<JsonObject>();
    material = std::make_shared<BlinnPhongMaterial>(materialObject);
}

bool Sphere::intersect(const Ray& ray, double tMin, double tMax, Hit& record) {
    const Vec3 originToCenter = center - ray.getOrigin();
    const auto a = ray.getDirection().lengthSquared();
    const auto h = ray.getDirection().dot(originToCenter);
    const auto c = originToCenter.lengthSquared() - radius * radius;
    auto discriminant = h*h - a*c;
    if (discriminant < 0)
        return false;

    auto sqrtD = std::sqrt(discriminant);

    auto root = (h - sqrtD) / a;
    if (root <= tMin || tMax <= root) {
        root = (h + sqrtD) / a;
        if (root <= tMin || tMax <= root)
            return false;
    }

    record.setT(root);
    record.setPoint(ray.at(record.getT()));
    record.setMaterial(material);

    Vec3 outwardNormal = (record.getPoint() - center) / radius;
    record.setFaceNormal(ray, outwardNormal);

    const auto normal = record.getNormal();
    const auto theta = std::atan2(normal.getZ(), normal.getX());
    const auto phi = std::acos(normal.getY());

    record.setUV((theta + M_PI) / (2 * M_PI), phi / M_PI);

    return true;
}
