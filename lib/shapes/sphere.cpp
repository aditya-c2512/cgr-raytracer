//
// Created by Aditya Choubey on 13/10/2025.
//
#include <shapes/sphere.h>

Sphere::Sphere(const Vec3& center, const double radius): center(center), radius(radius) {
}

Sphere::Sphere(const JsonObject &shapeObject) {
    const auto centerArray = shapeObject.at("location").as<JsonArray>();
    center = Vec3(centerArray[0].as<double>(), centerArray[1].as<double>(), centerArray[2].as<double>());
    radius = shapeObject.at("radius").as<double>();
}

bool Sphere::intersect(const Ray& ray) {
    return false;
}
