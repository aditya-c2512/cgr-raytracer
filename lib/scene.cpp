//
// Created by Aditya Choubey on 07/10/2025.
//

#include <scene.h>
#include <utils/json/json.h>

Scene::Scene(const std::string &path) {
    JsonObject sceneObject = Json::parse(path);
    auto objects = sceneObject["objects"].as<JsonArray>();
    JsonObject cameraObject;
    for (const auto& obj: objects) {
        if (obj.isObject() && (obj.as<JsonObject>().at("type").as<std::string>()) == "CAMERA") {
            cameraObject = obj.as<JsonObject>();
        }
    }

    camera = new Camera(cameraObject);
}

Scene::~Scene() {
    delete camera;
}

Camera * Scene::getCamera() const {
    return camera;
}
