//
// Created by Aditya Choubey on 19/09/2025.
//

#include <raytracer_app.h>
#include <utils/logger.h>
#include <math/ray.h>

RayTracerApp::RayTracerApp(const std::string& scenePath, const int imageWidth, const double aspectRatio, const std::string& filepath):
                            imageWidth(imageWidth), imageHeight(static_cast<int>(imageWidth / aspectRatio)),
                            camera(Camera(imageWidth, aspectRatio)), scene(scenePath) {
    image = new PpmImage(filepath, imageWidth, imageHeight);
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

    auto deltaU = camera.getDeltaU();
    auto deltaV = camera.getDeltaV();
    auto firstPixelPoint = camera.getFirstPixelPoint();
    auto cameraOrigin = camera.getOrigin();

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
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
