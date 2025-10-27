//
// Created by Aditya Choubey on 19/09/2025.
//

#include <ranges>
#include <raytracer_app.h>
#include <utils/logger.h>
#include <math/ray.h>

RayTracerApp::RayTracerApp(Scene* scene, const std::string& filepath): scene(scene) {
    image = new PpmImage(filepath, scene->getCamera()->getImageWidth(), scene->getCamera()->getImageHeight());
}

RayTracerApp::~RayTracerApp() {
    delete image;
}

Color RayTracerApp::trace(const Ray& ray) const {
    auto shapes = scene->getShapes();
    auto bvh = scene->getBVH();
    Color color = Color(0, 0, 0);

    const Vec3 unitDirection = ray.getDirection().normalize();
    auto a = 0.5 * (unitDirection.getY() + 1.0);
    color = Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;

    double minT = 500000;
    if (scene->canAccelerate()) {
        for (const auto bvhRoot: bvh->getRoots()) {
            Hit record;
            auto hit = bvhRoot->intersect(ray, 0, 500000, record);
            if (hit) {
                if (record.getT() < minT) {
                    minT = record.getT();
                    const auto& normal = record.getNormal();
                    color = Color(normal.getX(), normal.getY(), normal.getZ());
                }
            }
        }
    }
    else {
        for (auto shape: shapes | std::views::values) {
            Hit record;
            auto hit = shape->intersect(ray, 0, 500000, record);
            if (hit) {
                if (record.getT() < minT) {
                    minT = record.getT();
                    const auto& normal = record.getNormal();
                    color = Color(normal.getX(), normal.getY(), normal.getZ());
                }
            }
        }
    }

    logger->debug("Intersection point at ray " + std::to_string(minT));

    return color;
}

void RayTracerApp::run() const {
    logger->info("Starting up Raytracer App.");

    Camera* camera = scene->getCamera();

    logger->info("Starting Rendering Stage");
    for (int y = 0; y < camera->getImageHeight(); y++) {
        for (int x = 0; x < camera->getImageWidth(); x++) {
            Ray ray = camera->getRay(x, y);

            Color pixelColor = trace(ray);

            logger->debug("Color for pixel (" + std::to_string(x) + ", " + std::to_string(y) + "): " + pixelColor.toString());

            image->setPixel(x, y, pixelColor);
        }
        logger->info("Rendered Scanline #" + std::to_string(y+1));
    }
    logger->info("Finished Rendering Stage");

    image->write();
    logger->info("Finished up Raytracer App.");
}
