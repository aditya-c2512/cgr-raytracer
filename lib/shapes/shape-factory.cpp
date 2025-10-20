//
// Created by Aditya Choubey on 13/10/2025.
//

#include <shapes/shape-factory.h>
#include <shapes/sphere.h>
#include <shapes/cube.h>
#include <shapes/plane.h>

Logger* ShapeFactory::logger = Logger::getInstance();

Shape* ShapeFactory::createShape(const JsonObject &shapeObject) {
    const std::string shapeTypeValue = shapeObject.at("type").as<std::string>();
    switch (typeMap[shapeTypeValue]) {
        case SPHERE:
            return new Sphere(shapeObject);
        case PLANE:
            return new Plane(shapeObject);
        case CUBE:
            return new Cube(shapeObject);
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
