//
// Created by Aditya Choubey on 07/10/2025.
//

#include <scene.h>
#include <utils/json/json.h>

#include "shapes/shape-factory.h"

Scene::Scene(const std::string& scenePath, const std::string& bvhPath, double focusDistance) {
    JsonObject sceneObject = Json::parse(scenePath);
    auto sceneObjects = sceneObject["objects"].as<JsonArray>();
    JsonObject cameraObject;
    for (const auto& obj: sceneObjects) {
        if (!obj.isObject()) continue;

        auto objectName = obj.as<JsonObject>().at("name").as<std::string>();

        if (obj.as<JsonObject>().at("type").as<std::string>() == "CAMERA") {
            cameraObject = obj.as<JsonObject>();
        }
        else if (obj.as<JsonObject>().at("type").as<std::string>() == "POINT_LIGHT") {
            auto pointLightObject = obj.as<JsonObject>();
            auto* light = new PointLight(pointLightObject);
            lights.push_back(light);
        }
        else if (obj.as<JsonObject>().at("type").as<std::string>() == "AREA_LIGHT") {
            auto rectLightObject = obj.as<JsonObject>();
            auto* light = new RectLight(rectLightObject);
            lights.push_back(light);
        }
        else {
            shapes[objectName] = ShapeFactory::createShape(obj.as<JsonObject>());
        }
    }

    if (!bvhPath.empty()) {
        JsonObject bvhObject = Json::parse(bvhPath);
        bvh = new BoundingVolumeHierarchy(bvhObject, shapes);
        accelerate = true;
    }
    else {
        accelerate = false;
    }

    camera = new Camera(cameraObject, focusDistance);
}

Scene::~Scene() {
    delete camera;
    delete bvh;
    for (const auto& shape : shapes) delete shapes.at(shape.first);
}

Camera * Scene::getCamera() const {
    return camera;
}

std::map<std::string, Shape*> Scene::getShapes() const {
    return shapes;
}

BoundingVolumeHierarchy * Scene::getBVH() const {
    return bvh;
}

std::vector<Light*>& Scene::getLights() {
    return lights;
}

bool Scene::canAccelerate() const {
    return accelerate;
}
