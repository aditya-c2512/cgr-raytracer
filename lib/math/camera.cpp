//
// Created by Aditya Choubey on 22/09/2025.
//

#include <math/camera.h>

#include "math/utils.h"

Camera::Camera(const int imageWidth, const double aspectRatio) {
    int imHeight = static_cast<int>(imageWidth / aspectRatio);
    imHeight = (imHeight < 1) ? 1 : imHeight;

    this->imageWidth = imageWidth;
    this->imageHeight = imHeight;

    origin = Vec3(0, 0, 0);
    focalLength = 1.0;
    viewportHeight = 2.0;
    viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imHeight);

    const auto viewportU = Vec3(viewportWidth, 0, 0);
    const auto viewportV = Vec3(0, -viewportHeight, 0);

    deltaU = viewportU / imageWidth;
    deltaV = viewportV / imHeight;

    const Point3 viewportUpperLeft = origin - Vec3(0, 0, -focalLength) - viewportU/2 - viewportV/2;
    firstPixelPoint = viewportUpperLeft + (deltaU + deltaV) * 0.5;
}

Camera::Camera(const JsonObject &obj) {
    const auto originArray = obj.at("location").as<JsonArray>();
    origin = Vec3(originArray.at(0).as<double>(), originArray.at(1).as<double>(), originArray.at(2).as<double>());

    const auto lookAtArray = obj.at("gaze_direction").as<JsonArray>();
    lookAt = Vec3(lookAtArray.at(0).as<double>(), lookAtArray.at(1).as<double>(), lookAtArray.at(2).as<double>());

    verticalFov = obj.at("vertical_fov").as<double>();

    focalLength = (lookAt - origin).length();
    auto theta = degrees_to_radians(verticalFov);
    auto h = std::tan(theta/2);
    imageWidth = obj.at("film_resolution").as<JsonObject>().at("x").as<int>();

    double aspectRatio = obj.at("sensor_width").as<double>() / obj.at("sensor_height").as<double>();
    int imHeight = static_cast<int>(imageWidth / aspectRatio);
    imHeight = (imHeight < 1) ? 1 : imHeight;

    this->imageHeight = imHeight;
    viewportHeight = 2.0 * h * focalLength;
    viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imHeight);

    w = (origin - lookAt).normalize();
    u = vUp.cross(w).normalize();
    v = w.cross(u);

    const auto viewportU = u * viewportWidth;
    const auto viewportV = -v * viewportHeight;

    deltaU = viewportU / imageWidth;
    deltaV = viewportV / imHeight;

    const Point3 viewportUpperLeft = origin - w * focalLength - viewportU/2 - viewportV/2;
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

int Camera::getImageWidth() const {
    return imageWidth;
}

int Camera::getImageHeight() const {
    return imageHeight;
}
