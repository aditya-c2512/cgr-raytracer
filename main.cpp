#include <utils/logger.h>
#include <raytracer_app.h>

int main() {
    Logger* logger = Logger::getInstance();
    logger->setLogLevel(LOG_LEVEL_INFO);

    logger->info("Starting the application.");

    auto* app = new RayTracerApp(256, 256, "image.ppm");

    app->run();

    delete app;

    logger->info("Application finished.");
}