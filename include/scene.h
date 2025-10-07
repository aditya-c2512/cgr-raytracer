//
// Created by Aditya Choubey on 07/10/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_SCENE_H
#define CGR_RAYTRACER_SCENE_H
#include "shape.h"
#include "math/camera.h"

class Scene {
private:
    // Camera camera;
    // std::vector<Shape> shapes;

public:
    Scene(const std::string& path);
};

#endif //CGR_RAYTRACER_SCENE_H