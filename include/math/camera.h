//
// Created by Aditya Choubey on 22/09/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_CAMERA_H
#define CGR_RAYTRACER_CAMERA_H
#include "vec3.h"

class Camera {
private:
    Point3 origin;
    Vec3 up, right;
    double focalLength;
    double viewportWidth, viewportHeight;
    Vec3 deltaU, deltaV;
    Point3 firstPixelPoint;

public:
    Camera(int imageWidth, double aspectRatio);

    Point3 getOrigin() const;
    Vec3 getDeltaU() const;
    Vec3 getDeltaV() const;
    Point3 getFirstPixelPoint() const;
};

#endif //CGR_RAYTRACER_CAMERA_H