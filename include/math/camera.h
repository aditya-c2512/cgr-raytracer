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
    int samplesPerPixel;
    double shutterOpen, shutterClose;
    double lensRadius = 0.01;
    double focusDistance = 3.0;

public:
    explicit Camera(const JsonObject &obj, double focusDistance);

    Point3 getOrigin() const;
    int getImageWidth() const;
    int getImageHeight() const;
    Vec3 getForward() const { return forward; }
    int getSamplesPerPixel() const { return samplesPerPixel; }

    Ray getRay(int px, int py) const;

private:
    static Vec3 sampleSquare();
    static Vec3 sampleDisk();
};

#endif //CGR_RAYTRACER_CAMERA_H