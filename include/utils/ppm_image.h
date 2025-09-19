//
// Created by Aditya Choubey on 19/09/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_IMAGE_WRITER_H
#define CGR_RAYTRACER_IMAGE_WRITER_H
#include <string>
#include <vector>

#include "logger.h"

struct Color {
    double red;
    double green;
    double blue;
};

class PpmImage {
private:
    Logger* logger = Logger::getInstance();
    int width, height;
    std::vector<Color> pixels;

public:
    PpmImage(int width, int height);
    ~PpmImage();

    void setPixel(int x, int y, const Color &color);
    void writeFile(const std::string& fileName) const;
};


#endif //CGR_RAYTRACER_IMAGE_WRITER_H