//
// Created by Aditya Choubey on 19/09/2025.
//

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
    const Vec3 unitDirection = ray.getDirection().normalize();
    auto a = 0.5 * (unitDirection.getY() + 1.0);
    return Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;
}

void RayTracerApp::run() const {
    logger->info("Starting up Raytracer App.");

    Camera* camera = scene->getCamera();
    auto deltaU = camera->getDeltaU();
    auto deltaV = camera->getDeltaV();
    auto firstPixelPoint = camera->getFirstPixelPoint();
    auto cameraOrigin = camera->getOrigin();

    for (int y = 0; y < camera->getImageHeight(); y++) {
        for (int x = 0; x < camera->getImageWidth(); x++) {
            auto pixelCenter = firstPixelPoint + (deltaU * x) + (deltaV * y);
            auto rayDirection = pixelCenter - cameraOrigin;
            Ray ray(cameraOrigin, rayDirection);

            Color pixelColor = trace(ray);

            image->setPixel(x, y, pixelColor);
        }
    }
    image->write();
    logger->info("Finished up Raytracer App.");
}
