#include <utils/logger.h>
#include <utils/json/json.h>
#include <raytracer_app.h>

#include "utils/args-parser.h"

int main(int argc, char** argv) {
    Logger* logger = Logger::getInstance();
    logger->setLogLevel(LOG_LEVEL_INFO);

    auto* args = new ArgsParser(argc, argv);

    logger->info("Starting the application.");

    auto* scene = new Scene(args->getArg("scene").stringVal);

    const auto* app = new RayTracerApp(scene, args->getArg("render-output").stringVal);
    app->run();

    logger->info("Application finished.");

    delete app;
    delete scene;
    delete logger;

    return 0;
}
