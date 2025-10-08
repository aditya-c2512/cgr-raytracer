//
// Created by Aditya Choubey on 07/10/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_JSON_VALUE_H
#define CGR_RAYTRACER_JSON_VALUE_H
#include <string>
#include <unordered_map>
#include <vector>
#include <variant>

struct JsonValue;

using JsonObject = std::unordered_map<std::string, JsonValue>;
using JsonArray  = std::vector<JsonValue>;

struct JsonValue {
    using ValueType = std::variant<
        std::nullptr_t,
        bool,
        int,
        double,
        std::string,
        JsonArray,
        JsonObject
    >;

    ValueType value;

    JsonValue() : value(nullptr) {}
    explicit JsonValue(bool b) : value(b) {}
    explicit JsonValue(int i) : value(i) {}
    explicit JsonValue(double d) : value(d) {}
    explicit JsonValue(std::string s) : value(std::move(s)) {}
    explicit JsonValue(JsonArray a) : value(std::move(a)) {}
    explicit JsonValue(JsonObject o) : value(std::move(o)) {}

    std::string asString() const {
        if (auto p = std::get_if<std::string>(&value)) return *p;
        throw std::runtime_error("Value is not a string");
    }

    template<typename T>
    const T& as() const {
        if (auto p = std::get_if<T>(&value))
            return *p;
        throw std::runtime_error("Type mismatch in JsonValue::as<T>()");
    }

    bool isObject() const { return std::holds_alternative<JsonObject>(value); }
    bool isArray()  const { return std::holds_alternative<JsonArray>(value); }
    bool isString() const { return std::holds_alternative<std::string>(value); }
    bool isNumber() const { return std::holds_alternative<int>(value) || std::holds_alternative<double>(value); }
};

#endif //CGR_RAYTRACER_JSON_VALUE_H