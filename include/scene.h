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
#include <bvh.h>
#include <map>

class Scene {
private:
    Logger *logger = Logger::getInstance();
    Camera* camera;
    std::vector<Light*> lights;
    std::map<std::string, Shape*> shapes;
    BoundingVolumeHierarchy* bvh;

public:
    explicit Scene(const std::string& scenePath, const std::string& bvhPath);
    ~Scene();

    Camera* getCamera() const;
    std::map<std::string, Shape*> getShapes() const;
    BoundingVolumeHierarchy* getBVH() const;
};

#endif //CGR_RAYTRACER_SCENE_H