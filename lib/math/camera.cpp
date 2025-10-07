//
// Created by Aditya Choubey on 22/09/2025.
//

#include <math/camera.h>

Camera::Camera(const int imageWidth, const double aspectRatio) {
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    origin = Vec3(0, 0, 0);
    focalLength = 1.0;
    viewportHeight = 2.0;
    viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

    const auto viewportU = Vec3(viewportWidth, 0, 0);
    const auto viewportV = Vec3(0, -viewportHeight, 0);

    deltaU = viewportU / imageWidth;
    deltaV = viewportV / imageHeight;

    const Point3 viewportUpperLeft = origin - Vec3(0, 0, -focalLength) - viewportU/2 - viewportV/2;
    firstPixelPoint = viewportUpperLeft + (deltaU + deltaV) * 0.5;
}

Point3 Camera::getOrigin() const {
    return origin;
}

Vec3 Camera::getDeltaU() const {
    return deltaU;
}

Vec3 Camera::getDeltaV() const {
    return deltaV;
}

Point3 Camera::getFirstPixelPoint() const {
    return firstPixelPoint;
}
