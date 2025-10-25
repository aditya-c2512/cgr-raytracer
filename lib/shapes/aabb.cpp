//
// Created by Aditya Choubey on 25/10/2025.
//
#include <shapes/aabb.h>

AxisAlignedBBox::AxisAlignedBBox(const Vec3 &minPoint, const Vec3 &maxPoint): minPoint(minPoint), maxPoint(maxPoint) {}

AxisAlignedBBox::AxisAlignedBBox(const JsonObject &shapeObject) {
    minPoint = Vec3(shapeObject.at("xMin").as<double>(),
        shapeObject.at("yMin").as<double>(),
        shapeObject.at("zMin").as<double>());

    maxPoint = Vec3(shapeObject.at("xMax").as<double>(),
        shapeObject.at("yMax").as<double>(),
        shapeObject.at("zMax").as<double>());
}

bool AxisAlignedBBox::intersect(const Ray &ray, double tMin, double tMax, Hit &record) {
    for (int i = 0; i < 3; ++i) {
        double invD = 1.0 / ray.getDirection()[i];
        double t0 = (minPoint[i] - ray.getOrigin()[i]) * invD;
        double t1 = (maxPoint[i] - ray.getOrigin()[i]) * invD;

        // Swap if ray direction is negative
        if (invD < 0.0)
            std::swap(t0, t1);

        // Narrow down intersection interval
        tMin = std::max(tMin, t0);
        tMax = std::min(tMax, t1);

        // No intersection
        if (tMax <= tMin)
            return false;
    }

    // If we reach here, the ray intersects the box between tMin and tMax
    record.setT(tMin);
    record.setPoint(ray.at(tMin));

    return true;
}
