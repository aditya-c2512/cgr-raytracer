//
// Created by Aditya Choubey on 07/10/2025.
//

#include <scene.h>
#include <utils/json/json.h>

#include "shapes/shape-factory.h"

Scene::Scene(const std::string& scenePath, const std::string& bvhPath) {
    JsonObject sceneObject = Json::parse(scenePath);
    auto sceneObjects = sceneObject["objects"].as<JsonArray>();
    JsonObject cameraObject;
    for (const auto& obj: sceneObjects) {
        if (!obj.isObject()) continue;

        auto objectName = obj.as<JsonObject>().at("name").as<std::string>();

        if (obj.as<JsonObject>().at("type").as<std::string>() == "CAMERA") {
            cameraObject = obj.as<JsonObject>();
        } else if (obj.as<JsonObject>().at("type").as<std::string>() == "LIGHT") {}
        else {
            shapes[objectName] = ShapeFactory::createShape(obj.as<JsonObject>());
        }
    }

    if (!bvhPath.empty()) {
        JsonObject bvhObject = Json::parse(bvhPath);
        auto aabbObjects = bvhObject["objects"].as<JsonArray>();

        std::vector<BVHNode*> roots;

        for (const auto& aabbObject: aabbObjects) {
            auto aabbName = aabbObject.as<JsonObject>().at("name").as<std::string>();
            auto shape = shapes[aabbName];

            auto* bBox = new AxisAlignedBBox(aabbObject.as<JsonObject>());
            roots.push_back(new BVHNode(bBox, nullptr, nullptr, shape));
        }

        bvh = new BoundingVolumeHierarchy(roots);
        accelerate = true;
    }
    else {
        accelerate = false;
    }

    camera = new Camera(cameraObject);
}

Scene::~Scene() {
    delete camera;
    delete bvh;
    for (const auto& shape : shapes) delete shapes.at(shape.first);
    for (const auto light : lights) delete light;
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

bool Scene::canAccelerate() const {
    return accelerate;
}
