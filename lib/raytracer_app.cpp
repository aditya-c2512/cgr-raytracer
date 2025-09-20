//
// Created by Aditya Choubey on 19/09/2025.
//

#include <raytracer_app.h>
#include <utils/logger.h>

#include <utility>

RayTracerApp::RayTracerApp(const int imageWidth, const int imageHeight, std::string fileName): imageWidth(imageWidth), imageHeight(imageHeight), fileName(std::move(fileName)) {
    image = new PpmImage(imageWidth, imageHeight);
}

RayTracerApp::~RayTracerApp() {
    delete image;
}

void RayTracerApp::run() const {
    logger->info("Starting up Raytracer App.");

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            const double r = static_cast<double>(x) / (imageWidth - 1);
            const double g = static_cast<double>(y) / (imageHeight - 1);
            const double b = 0.0;

            image->setPixel(x, y, Color{r,g,b});
        }
    }
    image->writeFile(fileName);
    logger->info("Finished up Raytracer App.");
}
