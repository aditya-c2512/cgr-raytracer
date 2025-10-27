//
// Created by Aditya Choubey on 13/10/2025.
//

#ifndef CGR_RAYTRACER_ARGS_PARSER_H
#define CGR_RAYTRACER_ARGS_PARSER_H
#include <string>
#include <unordered_map>

#include "logger.h"

struct ArgsValue {
    int integerNum;
    double floatingNum;
    bool boolVal;
    std::string stringVal;
};

class ArgsParser {
private:
    Logger* logger = Logger::getInstance();
    std::unordered_map<std::string, ArgsValue> argMap;

    static bool isInteger(const std::string& s) {
        if (s.empty()) return false;
        char* end = nullptr;
        std::strtol(s.c_str(), &end, 10);
        return *end == '\0';
    }

    static bool isDouble(const std::string& s) {
        if (s.empty()) return false;
        char* end = nullptr;
        std::strtod(s.c_str(), &end);
        return *end == '\0';
    }

    static bool isQuotedString(const std::string& s) {
        return s.size() >= 2 && s.front() == '"' && s.back() == '"';
    }

    static std::string stripQuotes(const std::string& s) {
        if (isQuotedString(s))
            return s.substr(1, s.size() - 2);
        return s;
    }

public:
    ArgsParser(int argc, char** argv);
    ArgsValue get(const std::string& argName);
    bool contains(const std::string& argName) const;
};

#endif //CGR_RAYTRACER_ARGS_PARSER_H