//
// Created by Aditya Choubey on 22/09/2025.
//

#include <math/camera.h>

Camera::Camera(const JsonObject &obj) {
    const auto originArray = obj.at("location").as<JsonArray>();
    origin = Vec3(originArray.at(0).as<double>(), originArray.at(1).as<double>(), originArray.at(2).as<double>());

    const auto lookAtArray = obj.at("gaze_direction").as<JsonArray>();
    lookAt = Vec3(lookAtArray.at(0).as<double>(), lookAtArray.at(1).as<double>(), lookAtArray.at(2).as<double>());

    sensorWidth = obj.at("sensor_width_mm").as<double>() / 1000.0;
    sensorHeight = obj.at("sensor_height_mm").as<double>() / 1000.0;
    focalLength = obj.at("focal_length_mm").as<double>() / 1000.0;

    imageWidth = obj.at("film_resolution").as<JsonObject>().at("x").as<int>();

    double imHeightCalc = imageWidth * sensorHeight / sensorWidth;
    if (imHeightCalc < 1)
        imageHeight = obj.at("film_resolution").as<JsonObject>().at("y").as<int>();
    imageHeight = static_cast<int>(imHeightCalc);

    forward = (lookAt - origin).normalize();
    vUp = Vec3(0, 0, 1);

    right = forward.cross(vUp).normalize();
    up = right.cross(forward).normalize();
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

Ray Camera::getRay(int px, int py) const {
    double ndcX = (px + 0.5) / imageWidth;
    double ndcY = (py + 0.5) / imageHeight;

    double imagePlaneX = (ndcX - 0.5) * sensorWidth;
    double imagePlaneY = (0.5 - ndcY) * sensorHeight;

    // Ray direction in world space
    Vec3 pixelPos = origin + (forward * focalLength) + (right * imagePlaneX) + (up * imagePlaneY);

    Vec3 dir = (pixelPos - origin).normalize();

    return {origin, dir};
}
