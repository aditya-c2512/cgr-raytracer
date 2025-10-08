//
// Created by Aditya Choubey on 22/09/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_CAMERA_H
#define CGR_RAYTRACER_CAMERA_H
#include "vec3.h"
#include <utils/json/json.h>

class Camera {
private:
    Point3 origin;
    Vec3 lookAt;
    Vec3 vUp = Vec3(0,1,0);
    Vec3 u, v, w;
    double focalLength;
    int imageWidth, imageHeight;
    double verticalFov;
    double viewportWidth, viewportHeight;
    Vec3 deltaU, deltaV;
    Point3 firstPixelPoint;

public:
    Camera(int imageWidth, double aspectRatio);
    Camera(const JsonObject &obj);

    Point3 getOrigin() const;
    Vec3 getDeltaU() const;
    Vec3 getDeltaV() const;
    Point3 getFirstPixelPoint() const;
    int getImageWidth() const;
    int getImageHeight() const;
};

#endif //CGR_RAYTRACER_CAMERA_H