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
    PpmImage* image;
    Scene* scene;

public:
    // Initialisation
    RayTracerApp(Scene* scene, const std::string& outputPath);
    ~RayTracerApp();

    Color trace(const Ray& ray) const;
    void run() const;
};

#endif //CGR_RAYTRACER_RAYTRACER_APP_H