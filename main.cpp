#include <utils/logger.h>
#include <raytracer_app.h>

int main() {
    Logger* logger = Logger::getInstance();
    logger->setLogLevel(LOG_LEVEL_INFO);

    logger->info("Starting the application.");

    const auto* app = new RayTracerApp(256, 256, "../../Output/render.ppm");
    app->run();

    logger->info("Application finished.");

    delete app;
    delete logger;

    return 0;
}
