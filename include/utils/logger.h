//
// Created by Aditya Choubey on 19/09/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_LOG_H
#define CGR_RAYTRACER_LOG_H
#include <source_location>
#include <string>

enum LogLevel {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_NONE
};

class Logger {
private:
    LogLevel level;
    static Logger* instance;

private:
    Logger();
    static std::string getCurrentDateTime();

public:
    static Logger* getInstance();
    void setLogLevel(LogLevel logLevel);

    void debug(const std::string &message, const std::source_location& location = std::source_location::current()) const;
    void info(const std::string& message, const std::source_location& location = std::source_location::current()) const;
    void warn(const std::string& message, const std::source_location& location = std::source_location::current()) const;
    void error(const std::string& message, const std::source_location& location = std::source_location::current()) const;
};

#endif //CGR_RAYTRACER_LOG_H
