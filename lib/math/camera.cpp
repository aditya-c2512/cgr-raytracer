//
// Created by Aditya Choubey on 22/09/2025.
//

#include <math/camera.h>

Camera::Camera(const JsonObject &obj) {
    const auto originArray = obj.at("location").as<JsonArray>();
    origin = Vec3(originArray.at(0).as<double>(),
                  originArray.at(1).as<double>(),
                  originArray.at(2).as<double>());

    const auto lookAtArray = obj.at("gaze_direction").as<JsonArray>();
    lookAt = Vec3(lookAtArray.at(0).as<double>(),
                  lookAtArray.at(1).as<double>(),
                  lookAtArray.at(2).as<double>());

    sensorWidth = obj.at("sensor_width_m").as<double>();
    sensorHeight = obj.at("sensor_height_m").as<double>();
    focalLength = obj.at("focal_length_m").as<double>();  // Already in meters

    imageWidth = obj.at("film_resolution").as<JsonObject>().at("x").as<int>();
    double imHeightCalc = imageWidth * sensorHeight / sensorWidth;
    imageHeight = (imHeightCalc < 1) ? obj.at("film_resolution").as<JsonObject>().at("y").as<int>()
                                     : static_cast<int>(imHeightCalc);

    // --- Compute focal length from vertical FOV ---
    // vertical_fov is in degrees
    double vFOV = obj.at("vertical_fov").as<double>() * M_PI / 180.0;
    double hFOV = obj.at("horizontal_fov").as<double>() * M_PI / 180.0;

    // Compute focal length using vertical FOV (can switch to horizontal if desired)
    double f_v = (sensorHeight / 2.0) / std::tan(vFOV / 2.0);
    double f_h = (sensorWidth / 2.0) / std::tan(hFOV / 2.0);

    // Pick the smaller to avoid cropping
    focalLength = std::min(f_v, f_h);

    forward = (lookAt - origin).normalize();

    // Robust up vector: avoid colinear with forward
    vUp = (std::fabs(forward.dot(Vec3(0,0,1))) > 0.999) ? Vec3(0,1,0) : Vec3(0,0,1);

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

    Vec3 pixelPos = origin + (forward * focalLength) + (right * imagePlaneX) + (up * imagePlaneY);
    Vec3 dir = (pixelPos - origin).normalize();

    return {origin, dir};
}
