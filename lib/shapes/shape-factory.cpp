//
// Created by Aditya Choubey on 13/10/2025.
//

#include <shapes/shape-factory.h>
#include <shapes/sphere.h>

Logger* ShapeFactory::logger = Logger::getInstance();

Shape ShapeFactory::createShape(const JsonObject &shapeObject) {
    const std::string shapeTypeValue = shapeObject.at("type").as<std::string>();
    switch (typeMap[shapeTypeValue]) {
        case SPHERE:
            return Sphere(shapeObject);
        case PLANE:
            return {};
        case CUBE:
            return {};
        case CYLINDER:
            return {};
        case CONE:
            return {};
        case MESH:
            return {};
        default:
            logger->warn("Unknown shape type: " + shapeTypeValue);
            return {};
    }
}
