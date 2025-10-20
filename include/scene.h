//
// Created by Aditya Choubey on 07/10/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_SCENE_H
#define CGR_RAYTRACER_SCENE_H
#include <lights/light.h>
#include <shapes/shape.h>
#include <math/camera.h>
#include <utils/logger.h>

class Scene {
private:
    Logger *logger = Logger::getInstance();
    Camera* camera;
    std::vector<Light*> lights;
    std::vector<Shape*> shapes;

public:
    explicit Scene(const std::string& path);
    ~Scene();

    Camera* getCamera() const;
    std::vector<Shape*> getShapes() const;
};

#endif //CGR_RAYTRACER_SCENE_H