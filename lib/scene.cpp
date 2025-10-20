//
// Created by Aditya Choubey on 07/10/2025.
//

#include <scene.h>
#include <utils/json/json.h>

#include "shapes/shape-factory.h"

Scene::Scene(const std::string &path) {
    JsonObject sceneObject = Json::parse(path);
    auto objects = sceneObject["objects"].as<JsonArray>();
    JsonObject cameraObject;
    for (const auto& obj: objects) {
        if (!obj.isObject()) continue;

        if (obj.as<JsonObject>().at("type").as<std::string>() == "CAMERA") {
            cameraObject = obj.as<JsonObject>();
        } else if (obj.as<JsonObject>().at("type").as<std::string>() == "LIGHT") {}
        else {
            shapes.push_back(ShapeFactory::createShape(obj.as<JsonObject>()));
        }
    }

    camera = new Camera(cameraObject);
}

Scene::~Scene() {
    delete camera;
    for (auto shape : shapes) delete shape;
    for (auto light : lights) delete light;
}

Camera * Scene::getCamera() const {
    return camera;
}

std::vector<Shape*> Scene::getShapes() const {
    return shapes;
}
