//
// Created by Aditya Choubey on 19/09/2025.
//
#include <utils/logger.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

Logger* Logger::instance = nullptr;

Logger::Logger(): level(LOG_LEVEL_NONE) {};

Logger* Logger::getInstance() {
    if (instance == nullptr) {
        instance = new Logger();
    }

    return instance;
}

void Logger::setLogLevel(const LogLevel logLevel) {
    this->level = logLevel;
}

void Logger::debug(const std::string& message, const std::source_location& location) const {
    if (this->level != LOG_LEVEL_DEBUG) {
        return;
    }

    std::cout << "[DEBUG] " << getCurrentDateTime() << " | " << location.function_name() << " | " << message << std::endl;
}

void Logger::info(const std::string& message, const std::source_location& location) const {
    if (this->level != LOG_LEVEL_INFO && this->level != LOG_LEVEL_DEBUG) {
        return;
    }

    std::cout << "\033[32m[INFO] " << getCurrentDateTime() << " | " << location.function_name() << " | " << message << "\033[0m" << std::endl;
}

void Logger::warn(const std::string& message, const std::source_location& location) const {
    if (this->level != LOG_LEVEL_WARNING && this->level != LOG_LEVEL_INFO &&
        this->level != LOG_LEVEL_DEBUG) {
        return;
    }

    std::cout << "\033[33m[WARN] " << getCurrentDateTime() << " | " << location.function_name() << " | " << message << "\033[0m" << std::endl;
}

void Logger::error(const std::string& message, const std::source_location& location) const {
    if (this->level < LOG_LEVEL_ERROR && this->level != LOG_LEVEL_WARNING &&
        this->level != LOG_LEVEL_INFO && this->level != LOG_LEVEL_DEBUG) {
        return;
    }

    std::cout << "\033[31m[ERROR] " << getCurrentDateTime() << " | " << location.function_name() << " | " << message << "\033[0m" << std::endl;
}

std::string Logger::getCurrentDateTime() {
    // Get current time
    const auto now = std::chrono::system_clock::now();
    const std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Format to YYYY-MM-DD HH:MM:SS
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
