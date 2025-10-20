//
// Created by Aditya Choubey on 20/10/2025.
//
#include <shapes/plane.h>

Plane::Plane(const Point3 &point, const Vec3 &normal): point(point), normal(normal) {
}

Plane::Plane(const JsonObject &shapeObject) {
    auto cornerObjects = shapeObject.at("corners").as<JsonArray>();
    Point3 corners[4];
    for (int i = 0; i < cornerObjects.size(); i++) {
        auto cornerObject = cornerObjects[i].as<JsonArray>();
        corners[i] = Point3(cornerObject[0].as<double>(), cornerObject[1].as<double>(), cornerObject[2].as<double>());
    }

    point = corners[0];

    Vec3 edge1 = corners[1] - corners[0];  // vector from corner0 to corner1
    Vec3 edge2 = corners[2] - corners[0];  // vector from corner0 to corner2

    normal = edge1.cross(edge2).normalize();
}

bool Plane::intersect(const Ray &ray, double tMin, double tMax, Hit &record) {
    if (const auto den = normal.dot(ray.getDirection()); std::abs(den) > 1e-6) {
        const auto t = (point - ray.getOrigin()).dot(normal) / den;
        return (t >= 0);
    }

    return false;
}
