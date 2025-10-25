//
// Created by Aditya Choubey on 22/09/2025.
//

#include <math/camera.h>

Camera::Camera(const JsonObject &obj) {
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
    double ndcX = (px + 0.5) / imageWidth;
    double ndcY = (py + 0.5) / imageHeight;

    double imagePlaneX = (ndcX - 0.5) * sensorWidth;
    double imagePlaneY = (0.5 - ndcY) * sensorHeight;

    Vec3 dir = (right * imagePlaneX) + (up * imagePlaneY) - (forward * focalLength);

    return {origin, dir.normalize()};
}
