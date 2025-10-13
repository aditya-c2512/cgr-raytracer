//
// Created by Aditya Choubey on 13/10/2025.
//

#include <utils/args-parser.h>

ArgsParser::ArgsParser(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.rfind("--", 0) != 0) {
            logger->warn("Ignoring unrecognized argument format: " + arg);
            continue;
        }

        // Strip leading "--"
        arg = arg.substr(2);
        auto pos = arg.find('=');
        if (pos == std::string::npos) {
            logger->warn("Ignoring argument without '=': " + arg);
            continue;
        }

        std::string key = arg.substr(0, pos);
        std::string value = arg.substr(pos + 1);

        ArgsValue parsedValue;

        if (isInteger(value)) {
            parsedValue.integerNum = std::stoi(value);
        } else if (isDouble(value)) {
            parsedValue.floatingNum = std::stod(value);
        } else if (isQuotedString(value)) {
            parsedValue.stringVal = stripQuotes(value);
        } else {
            parsedValue.stringVal = value;
        }

        argMap[key] = parsedValue;
        logger->info("Parsed argument: --" + key + "=" + value);
    }
}

ArgsValue ArgsParser::getArg(const std::string& argName) {
    if (!argMap.contains(argName)) {
        logger->error("Argument '" + argName + "' not found.");
    }

    return argMap.at(argName);
}
