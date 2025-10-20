//
// Created by Aditya Choubey on 22/09/2025.
//

#include <math/camera.h>

Camera::Camera(const JsonObject &obj) {
    const auto originArray = obj.at("location").as<JsonArray>();
    origin = Vec3(originArray.at(0).as<double>(), originArray.at(1).as<double>(), originArray.at(2).as<double>());

    const auto lookAtArray = obj.at("gaze_direction").as<JsonArray>();
    lookAt = Vec3(lookAtArray.at(0).as<double>(), lookAtArray.at(1).as<double>(), lookAtArray.at(2).as<double>());

    sensorWidth = obj.at("sensor_width_mm").as<double>();
    sensorHeight = obj.at("sensor_height_mm").as<double>();
    focalLength = obj.at("focal_length_mm").as<double>();

    imageWidth = obj.at("film_resolution").as<JsonObject>().at("x").as<int>();

    double imHeightCalc = imageWidth * sensorHeight / sensorWidth;
    if (imHeightCalc < 1)
        imageHeight = obj.at("film_resolution").as<JsonObject>().at("y").as<int>();
    imageHeight = static_cast<int>(imHeightCalc);

    forward = lookAt.normalize();
    vUp = Vec3(0, 0, 1);
    if (std::fabs(vUp.dot(forward)) > 0.999)
        vUp = Vec3(0, 1, 0); // avoid degeneracy

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
    double ndcX = (px + 0.5) / imageWidth * 2.0 - 1.0;
    double ndcY = 1.0 - (py + 0.5) / imageHeight * 2.0; // flip Y

    // Image plane in world units (mm)
    double imagePlaneX = ndcX * (sensorWidth / 2.0);
    double imagePlaneY = ndcY * (sensorHeight / 2.0);

    // Ray direction in world space
    Vec3 pixelPos = origin + (forward * focalLength) + (right * imagePlaneX) + (up * imagePlaneY);

    Vec3 dir = (pixelPos - origin).normalize();

    return {origin, dir};
}
