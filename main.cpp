#include <utils/logger.h>
#include <utils/json/json.h>
#include <utils/args-parser.h>
#include <raytracer_app.h>

void printHelp() {
    std::cout << "\n=== Command Line Arguments Help ===\n";
    std::cout << std::left << std::setw(20) << "Argument"
              << std::setw(12) << "Required"
              << "Description\n";
    std::cout << std::string(60, '-') << "\n";

    std::cout << std::left << std::setw(20) << "--help"
                  << std::setw(12) << "No"
                  << "Get help on application usage and argument descriptions." << "\n";
    std::cout << std::left << std::setw(20) << "--scene"
                  << std::setw(12) << "Yes"
                  << "Provide the absolute or relative path of a JSON object describing the scene to be rendered." << "\n";
    std::cout << std::left << std::setw(20) << "--render-output"
                  << std::setw(12) << "No"
                  << "Provide the absolute or relative path to where the rendered image should be written to." << "\n";

    std::cout << "\nExample usage:\n"
              << "  ./program --scene=\"/my/input/path/scene.json\" --render-output=\"/my/output/path/render.ppm\"\n"
              << std::endl;
}

int main(int argc, char** argv) {
    Logger* logger = Logger::getInstance();
    logger->setLogLevel(LOG_LEVEL_INFO);

    auto* args = new ArgsParser(argc, argv);

    if (args->get("help").boolVal) {
        printHelp();
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
