#include <utils/logger.h>
#include <utils/json/json.h>
#include <raytracer_app.h>

int main(int argc, char** argv) {
    Logger* logger = Logger::getInstance();
    logger->setLogLevel(LOG_LEVEL_INFO);

    logger->info("Starting the application.");

    auto* scene = new Scene("../../Blend/scene_export.json");

    const auto* app = new RayTracerApp(scene, "../../Output/render.ppm");
    app->run();

    logger->info("Application finished.");

    delete app;
    delete scene;
    delete logger;

    return 0;
}
