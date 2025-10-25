//
// Created by Aditya Choubey on 22/09/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_CAMERA_H
#define CGR_RAYTRACER_CAMERA_H
#include "vec3.h"
#include <utils/json/json.h>

#include "ray.h"

class Camera {
private:
    Point3 origin;
    Vec3 gazeDirection;
    Vec3 vUp;
    Vec3 up, forward, right;
    double focalLength;
    int imageWidth, imageHeight;
    double sensorWidth, sensorHeight;

public:
    explicit Camera(const JsonObject &obj);

    Point3 getOrigin() const;
    int getImageWidth() const;
    int getImageHeight() const;
    Vec3 getForward() const { return forward; }

    Ray getRay(int px, int py) const;
};

#endif //CGR_RAYTRACER_CAMERA_H