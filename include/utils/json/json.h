//
// Created by Aditya Choubey on 07/10/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_JSON_H
#define CGR_RAYTRACER_JSON_H

#include <fstream>
#include <sstream>
#include <utils/logger.h>
#include <utils/json/json_value.h>

namespace Json
{
    inline Logger* logger = Logger::getInstance();
    class Parser {
    public:
        explicit Parser(const std::string &text) : src(text), pos(0) {}

        JsonValue parse() {
            skipWhitespace();
            JsonValue val = parseValue();
            skipWhitespace();
            if (pos != src.size())
                logger->error("Unexpected characters after JSON root");
            return val;
        }

    private:
        const std::string &src;
        size_t pos;

        void skipWhitespace() {
            while (pos < src.size() && std::isspace(static_cast<unsigned char>(src[pos])))
                ++pos;
        }

        char peek() const { return pos < src.size() ? src[pos] : '\0'; }
        char get() { return pos < src.size() ? src[pos++] : '\0'; }

        JsonValue parseValue() {
            skipWhitespace();
            char c = peek();
            if (c == '{') return parseObject();
            if (c == '[') return parseArray();
            if (c == '"') return parseString();
            if (std::isdigit(c) || c == '-' || c == '+') return parseNumber();
            if (src.compare(pos, 4, "true") == 0)  { pos += 4; return JsonValue(true); }
            if (src.compare(pos, 5, "false") == 0) { pos += 5; return JsonValue(false); }
            if (src.compare(pos, 4, "null") == 0)  { pos += 4; return JsonValue(nullptr); }
            logger->error("Invalid JSON value at position " + std::to_string(pos));
            return {};
        }

        JsonValue parseObject() {
            JsonObject obj;
            get(); // consume '{'
            skipWhitespace();
            if (peek() == '}') { get(); return JsonValue(obj); }

            while (true) {
                skipWhitespace();
                std::string key = parseString().asString();
                skipWhitespace();
                if (get() != ':') logger->error("Expected ':' after key");
                skipWhitespace();
                obj[key] = parseValue();
                skipWhitespace();
                char c = get();
                if (c == '}') break;
                if (c != ',') logger->error("Expected ',' or '}' in object");
            }
            return JsonValue(obj);
        }

        JsonValue parseArray() {
            JsonArray arr;
            get(); // consume '['
            skipWhitespace();
            if (peek() == ']') { get(); return JsonValue(arr); }

            while (true) {
                arr.push_back(parseValue());
                skipWhitespace();
                const char c = get();
                if (c == ']') break;
                if (c != ',') logger->error("Expected ',' or ']' in array");
            }
            return JsonValue(arr);
        }

        JsonValue parseString() {
            if (get() != '"') logger->error("Expected '\"' at start of string");
            std::string result;
            while (true) {
                char c = get();
                if (c == '"') break;
                if (c == '\\') {
                    switch (char next = get()) {
                        case '"': result += '"'; break;
                        case '\\': result += '\\'; break;
                        case '/': result += '/'; break;
                        case 'b': result += '\b'; break;
                        case 'f': result += '\f'; break;
                        case 'n': result += '\n'; break;
                        case 'r': result += '\r'; break;
                        case 't': result += '\t'; break;
                        default: logger->error("Invalid escape sequence");
                    }
                } else {
                    result += c;
                }
            }
            return JsonValue(result);
        }

        JsonValue parseNumber() {
            size_t start = pos;
            if (peek() == '-' || peek() == '+') get();
            while (std::isdigit(peek())) get();
            bool isDouble = false;
            if (peek() == '.') {
                isDouble = true;
                get();
                while (std::isdigit(peek())) get();
            }
            std::string num = src.substr(start, pos - start);
            try {
                if (isDouble)
                    return JsonValue(std::stod(num));
                return JsonValue(std::stoi(num));
            } catch (...) {
                logger->error("Invalid number at position " + std::to_string(start));
            }
            return {};
        }
    };

    inline JsonObject parse(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open())
            logger->error("Could not open file: " + filename);

        std::ostringstream ss;
        ss << file.rdbuf();
        std::string content = ss.str();

        Parser parser(content);
        JsonValue root = parser.parse();

        if (auto obj = std::get_if<JsonObject>(&root.value))
            return *obj;

        throw std::runtime_error("Root element is not a JSON object");
    }
}

#endif //CGR_RAYTRACER_JSON_H