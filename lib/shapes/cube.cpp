//
// Created by Aditya Choubey on 20/10/2025.
//
#include <shapes/cube.h>
#include <math/matrix3x3.h>

Cube::Cube(const Point3 &min, const Point3 &max): minPoint(min), maxPoint(max) {
}

Cube::Cube(const JsonObject &shapeObject) {
    auto locationArray = shapeObject.at("location").as<JsonArray>();
    auto location = Vec3(locationArray[0].as<double>(), locationArray[1].as<double>(), locationArray[2].as<double>());

    auto rotationArray = shapeObject.at("rotation_euler").as<JsonArray>();
    auto rotation = Vec3(rotationArray[0].as<double>(), rotationArray[1].as<double>(), rotationArray[2].as<double>());

    auto sideLength = shapeObject.at("scale").as<double>();
    Matrix3x3 absR = Matrix3x3::rotationFromEulerZYX(rotation).abs();
    double h = sideLength / 2.0;
    Vec3 e = {h, h, h};

    Vec3 w = absR * e;

    minPoint = { location.getX() - w.getX(), location.getY() - w.getY(), location.getZ() - w.getZ() };
    maxPoint = { location.getX() + w.getX(), location.getY() + w.getY(), location.getZ() + w.getZ() };
}

bool Cube::intersect(const Ray &ray, double tMin, double tMax, Hit &record) {
    double t0 = tMin;
    double t1 = tMax;

    Vec3 normal; // normal of hit face

    // For each axis: find intersection with the slabs
    for (int i = 0; i < 3; ++i) {
        double invD = 1.0 / ray.getDirection()[i];
        double tNear = (minPoint[i] - ray.getOrigin()[i]) * invD;
        double tFar  = (maxPoint[i] - ray.getOrigin()[i]) * invD;

        // swap if needed
        if (invD < 0.0) std::swap(tNear, tFar);

        // Update t0 and t1 for the interval
        if (tNear > t0) {
            t0 = tNear;
            // set normal according to which face we hit
            normal = Vec3(0, 0, 0);
            normal[i] = (invD > 0) ? -1 : 1; // direction of normal
        }
        t1 = std::min(t1, tFar);

        // If no overlap, no hit
        if (t1 <= t0)
            return false;
    }

    // At this point, t0 is the first intersection distance
    record.setT(t0);
    record.setPoint(ray.at(t0));
    record.setNormal(normal);
    record.setColor(Color(0, 1, 0));

    return true;
}
