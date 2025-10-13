#include <utils/logger.h>
#include <utils/json/json.h>
#include <utils/args-parser.h>
#include <raytracer_app.h>

int main(int argc, char** argv) {
    Logger* logger = Logger::getInstance();
    logger->setLogLevel(LOG_LEVEL_INFO);

    auto* args = new ArgsParser(argc, argv);

    if (args->get("help").boolVal) {
        logger->info("Usage: raytracer [OPTIONS]");
        return EXIT_SUCCESS;
    }

    logger->info("Starting the application.");

    auto* scene = new Scene(args->get("scene").stringVal);

    const auto* app = new RayTracerApp(scene, args->get("render-output").stringVal);
    app->run();

    logger->info("Application finished.");

    delete app;
    delete scene;
    delete logger;

    return EXIT_SUCCESS;
}
