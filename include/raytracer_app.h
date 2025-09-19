//
// Created by Aditya Choubey on 19/09/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_RAYTRACER_APP_H
#define CGR_RAYTRACER_RAYTRACER_APP_H
#include "utils/logger.h"
#include "utils/ppm_image.h"

class RayTracerApp {
private:
    Logger* logger = Logger::getInstance();
    int imageWidth, imageHeight;
    std::string fileName;
    PpmImage* image;

public:
    RayTracerApp(int imageWidth, int imageHeight, std::string fileName);
    ~RayTracerApp();

    void run();
};

#endif //CGR_RAYTRACER_RAYTRACER_APP_H