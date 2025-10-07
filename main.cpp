#include <utils/logger.h>
#include <raytracer_app.h>

int main() {
    Logger* logger = Logger::getInstance();
    logger->setLogLevel(LOG_LEVEL_INFO);

    logger->info("Starting the application.");

    const auto* app = new RayTracerApp("../../Blend/scene_export.json", 400, 16.0/9.0, "../../Output/render.ppm");
    app->run();

    logger->info("Application finished.");

    delete app;
    delete logger;

    return 0;
}
