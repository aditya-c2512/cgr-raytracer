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
    Vec3 edge2 = corners[3] - corners[0]; // use corner3 instead of corner2
    normal = edge1.cross(edge2).normalize();
    if (normal.getY() < 0) normal = -normal;
}

bool Plane::intersect(const Ray &ray, double tMin, double tMax, Hit &record) {
    // --- Step 1: Ray-plane intersection ---
    const double denom = normal.dot(ray.getDirection());
    if (std::abs(denom) < 1e-6)  // Ray parallel to plane
        return false;

    const double t = (point - ray.getOrigin()).dot(normal) / denom;
    if (t < tMin || t > tMax)
        return false;

    Point3 p = ray.getOrigin() + ray.getDirection() * t;

    // --- Step 2: Check if intersection point is inside the 4-corner polygon ---
    for (int i = 0; i < 4; ++i) {
        Vec3 edge = (corners[(i+1)%4] - corners[i]); // Edge vector
        Vec3 vp = p - corners[i];                 // Vector from corner to point
        if (normal.dot(edge.cross(vp)) < 0) {
            // Outside if negative
            logger->debug("Point is outside bounds: (" + std::to_string(p.getX()) + ", " + std::to_string(p.getY()) + ", " + std::to_string(p.getZ()) + ")");
            return false;
        }
    }

    // --- Step 3: Fill hit record ---
    record.setT(t);
    record.setPoint(p);
    record.setNormal((denom < 0) ? normal : -normal); // Always point against ray
    record.setColor(Color(0,0,1));

    return true;
}