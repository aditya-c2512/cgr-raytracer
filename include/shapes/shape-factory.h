//
// Created by Aditya Choubey on 13/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_SHAPE_FACTORY_H
#define CGR_RAYTRACER_SHAPE_FACTORY_H

#include <map>
#include <shapes/shape.h>
#include <utils/logger.h>
#include <utils/json/json_value.h>
#include <math/ray.h>

enum ShapeType {
    SPHERE,
    PLANE,
    CUBE,
    CONE,
    CYLINDER,
    MESH,
};

class ShapeFactory {
private:
    static Logger* logger;

public:
    inline static std::map<std::string, ShapeType> typeMap = {
        {"SPHERE", SPHERE}, {"PLANE", PLANE}, {"CUBE", CUBE},
        {"CONE", CONE}, {"CYLINDER", CYLINDER}, {"MESH", MESH}
    };

    ShapeFactory() = default;
    ~ShapeFactory() = default;

    static Shape* createShape(const JsonObject &shapeObject);
};


#endif //CGR_RAYTRACER_SHAPE_FACTORY_H
