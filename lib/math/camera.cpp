//
// Created by Aditya Choubey on 22/09/2025.
//

#include <math/camera.h>

#include "math/utils.h"

Camera::Camera(const JsonObject &obj, double focusDistance): focusDistance(focusDistance) {
    const auto originArray = obj.at("location").as<JsonArray>();
    origin = Vec3(originArray.at(0).as<double>(),
                  originArray.at(1).as<double>(),
                  originArray.at(2).as<double>());

    const auto gazeDirectionArray = obj.at("gaze_direction").as<JsonArray>();
    gazeDirection = Vec3(gazeDirectionArray.at(0).as<double>(),
                  gazeDirectionArray.at(1).as<double>(),
                  gazeDirectionArray.at(2).as<double>());

    sensorWidth = obj.at("sensor_width_mm").as<double>() * 0.001;
    sensorHeight = obj.at("sensor_height_mm").as<double>() * 0.001;
    focalLength = obj.at("focal_length_mm").as<double>() * 0.001;

    imageWidth = obj.at("film_resolution").as<JsonObject>().at("x").as<int>();
    double imHeightCalc = imageWidth * sensorHeight / sensorWidth;
    imageHeight = (imHeightCalc < 1) ? obj.at("film_resolution").as<JsonObject>().at("y").as<int>()
                                     : static_cast<int>(imHeightCalc);

    samplesPerPixel = obj.at("samples").as<int>();

    vUp = {0, 0, 1};
    forward = gazeDirection.normalize();
    right = vUp.cross(forward).normalize();
    up = forward.cross(right).normalize();
}

Point3 Camera::getOrigin() const {
    return origin;
}


int Camera::getImageWidth() const {
    return imageWidth;
}

int Camera::getImageHeight() const {
    return imageHeight;
}

Ray Camera::getRay(const int px, const int py) const {
    // pixel jitter for anti-aliasing
    auto offset = sampleSquare();
    double ndcX = (px + offset.getX() + 0.5) / imageWidth;
    double ndcY = (py + offset.getY() + 0.5) / imageHeight;

    double imagePlaneX = (ndcX - 0.5) * sensorWidth;
    double imagePlaneY = (0.5 - ndcY) * sensorHeight;

    // direction from camera for perfect pinhole ray
    Vec3 baseDir = (right * imagePlaneX) + (up * imagePlaneY) - (forward * focalLength);
    baseDir = baseDir.normalize();

    // Point where this ray intersects the focus plane
    Point3 focusPoint = origin + baseDir * focusDistance;

    // Sample random point on lens to simulate aperture
    Vec3 lensSample = sampleDisk() * lensRadius;
    Point3 lensOrigin = origin + right * lensSample.getX() + up * lensSample.getY();

    // New direction passing through focus point
    Vec3 defocusDir = (focusPoint - lensOrigin).normalize();

    // Time for motion blur if you support it
    double time = mathutils::getRandom(shutterOpen, shutterClose);

    return Ray(lensOrigin, defocusDir, time);
}

Vec3 Camera::sampleSquare() {
    return {mathutils::getRandom(0,1) - 0.5, mathutils::getRandom(0,1) - 0.5, 0};
}

Vec3 Camera::sampleDisk() {
    double u = mathutils::getRandom(0,1) * 2.0 - 1.0;
    double v = mathutils::getRandom(0,1) * 2.0 - 1.0;

    if (u == 0 && v == 0) return {0, 0, 0};

    double r, theta;
    if (abs(u) > abs(v)) {
        r = u;
        theta = (M_PI / 4.0) * (v / u);
    } else {
        r = v;
        theta = (M_PI / 2.0) - (M_PI / 4.0) * (u / v);
    }

    return {r * cos(theta), r * sin(theta), 0};
}
