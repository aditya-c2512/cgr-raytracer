//
// Created by Aditya Choubey on 20/10/2025.
//
#include <shapes/plane.h>

Plane::Plane(const Point3 &point, const Vec3 &normal): point(point), normal(normal) {
}

Plane::Plane(const JsonObject &shapeObject) {
    auto cornerObjects = shapeObject.at("corners").as<JsonArray>();
    for (int i = 0; i < cornerObjects.size(); i++) {
        auto cornerObject = cornerObjects[i].as<JsonArray>();
        corners[i] = Point3(cornerObject[0].as<double>(), cornerObject[1].as<double>(), cornerObject[2].as<double>());
    }

    point = corners[0];

    Vec3 edge1 = corners[1] - corners[0];
    Vec3 edge2 = corners[3] - corners[0];

    normal = edge1.cross(edge2).normalize();
}

bool Plane::intersect(const Ray &ray, double tMin, double tMax, Hit &record) {
    double denom = ray.getDirection().dot(normal);
    if (std::fabs(denom) < 1e-8)
        return false;  // Parallel to plane

    double t = (point - ray.getOrigin()).dot(normal) / denom;
    if (t < tMin || t > tMax)
        return false;

    Point3 hitPoint = ray.getOrigin() + ray.getDirection() * t;

    // Check if inside the quadrilateral
    if (!isInside(hitPoint))
        return false;

    record.setT(t);
    record.setPoint(hitPoint);
    record.setNormal(normal);
    record.setColor(Color(0, 0, 1));

    return true;
}

bool Plane::isInside(const Point3 &p) const {
    for (int i = 0; i < 4; ++i) {
        const Point3 &a = corners[i];
        const Point3 &b = corners[(i + 1) % 4];
        Vec3 edge = b - a;
        Vec3 toPoint = p - a;
        Vec3 crossProd = edge.cross(toPoint);

        // If point is outside (cross product not facing same side as normal)
        if (crossProd.dot(normal) < 0)
            return false;
    }
    return true;
}