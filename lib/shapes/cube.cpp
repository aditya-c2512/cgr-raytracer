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

    auto sideLength = shapeObject.at("scale").as<double>() * 1;
    Matrix3x3 absR = Matrix3x3::rotationFromEulerZYX(rotation).abs();
    double h = sideLength / 2.0;
    Vec3 e = {h, h, h};

    Vec3 w = absR * e;

    minPoint = { location.getX() - w.getX(), location.getY() - w.getY(), location.getZ() - w.getZ() };
    maxPoint = { location.getX() + w.getX(), location.getY() + w.getY(), location.getZ() + w.getZ() };
}

bool Cube::intersect(const Ray &ray, double tMin, double tMax, Hit &record) {
    auto minX = (minPoint.getX() - ray.getOrigin().getX()) / ray.getDirection().getX();
    auto maxX = (maxPoint.getX() - ray.getOrigin().getX()) / ray.getDirection().getX();

    if (minX > maxX) std::swap(minX, maxX);

    auto minY = (minPoint.getY() - ray.getOrigin().getY()) / ray.getDirection().getY();
    auto maxY = (maxPoint.getY() - ray.getOrigin().getY()) / ray.getDirection().getY();

    if (minY > maxY) std::swap(minY, maxY);

    if ((minX > maxY) || (minY > maxX))
        return false;

    if (minY > minX) minX = minY;
    if (maxY < maxX) maxX = maxY;

    auto minZ = (minPoint.getZ() - ray.getOrigin().getZ()) / ray.getDirection().getZ();
    auto maxZ = (maxPoint.getZ() - ray.getOrigin().getZ()) / ray.getDirection().getZ();

    if (minZ > maxZ) std::swap(minZ, maxZ);

    if ((minX > maxZ) || (minZ > maxX))
        return false;

    if (minZ > minX) minX = minZ;
    if (maxZ < maxX) maxX = maxZ;

    return true;
}
