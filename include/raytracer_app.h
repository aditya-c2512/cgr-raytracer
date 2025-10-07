//
// Created by Aditya Choubey on 19/09/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_RAYTRACER_APP_H
#define CGR_RAYTRACER_RAYTRACER_APP_H
#include <math/camera.h>
#include <utils/logger.h>
#include <utils/ppm_image.h>

#include "scene.h"
#include "math/ray.h"

class RayTracerApp {
private:
    Logger* logger = Logger::getInstance();
    int imageWidth, imageHeight;
    PpmImage* image;
    Camera camera;
    Scene scene;

public:
    // Initialisation
    RayTracerApp(const std::string& scenePath, int imageWidth, double aspectRatio, const std::string& outputPath);
    ~RayTracerApp();

    Color trace(const Ray& ray) const;
    void run() const;
};

#endif //CGR_RAYTRACER_RAYTRACER_APP_H