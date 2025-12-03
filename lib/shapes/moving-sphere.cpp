//
// Created by Aditya Choubey on 01/12/2025.
//
#include <shapes/moving-sphere.h>

#include "materials/blinn-phong-material.h"

MovingSphere::MovingSphere(const Vec3 &startCenter, const Vec3 &endCenter, double radius):
    radius(radius), startCenter(startCenter), endCenter(endCenter) {}

MovingSphere::MovingSphere(const JsonObject &shapeObject) {
    const auto startArray = shapeObject.at("start_location").as<JsonArray>();
    startCenter = Vec3(startArray[0].as<double>(), startArray[1].as<double>(), startArray[2].as<double>());

    const auto endArray = shapeObject.at("end_location").as<JsonArray>();
    endCenter = Vec3(endArray[0].as<double>(), endArray[1].as<double>(), endArray[2].as<double>());

    radius = shapeObject.at("radius").as<double>() * 1;

    auto materialObject = shapeObject.at("material").as<JsonObject>();
    material = std::make_shared<BlinnPhongMaterial>(materialObject);
}

bool MovingSphere::intersect(const Ray &ray, double tMin, double tMax, Hit &record) {
    // Compute interpolated center based on ray time
    Vec3 centerAtTime = startCenter + (endCenter - startCenter) * ray.getTime();

    const Vec3 originToCenter = centerAtTime - ray.getOrigin();
    const auto a = ray.getDirection().lengthSquared();
    const auto h = ray.getDirection().dot(originToCenter);
    const auto c = originToCenter.lengthSquared() - radius * radius;
    auto discriminant = h*h - a*c;
    if (discriminant < 0) {
        return false;
    }

    auto sqrtD = std::sqrt(discriminant);

    auto root = (h - sqrtD) / a;
    if (root <= tMin || tMax <= root) {
        root = (h + sqrtD) / a;
        if (root <= tMin || tMax <= root) {
            return false;
        }
    }

    record.setT(root);
    record.setPoint(ray.at(record.getT()));
    record.setMaterial(material);

    Vec3 outwardNormal = (record.getPoint() - centerAtTime) / radius;
    record.setFaceNormal(ray, outwardNormal);

    const auto normal = record.getNormal();
    const auto theta = std::atan2(normal.getZ(), normal.getX());
    const auto phi = std::acos(normal.getY());

    record.setUV((theta + M_PI) / (2 * M_PI), phi / M_PI);
    // logger->debug("UV coordinates: " + std::to_string(record.getU()) + "," + std::to_string(record.getV()));

    return true;
}
