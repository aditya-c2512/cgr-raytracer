//
// Created by Aditya Choubey on 19/09/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_IMAGE_WRITER_H
#define CGR_RAYTRACER_IMAGE_WRITER_H
#include <string>
#include <vector>
#include <math/color.h>

#include "image.h"
#include "logger.h"

class PpmImage : public Image {
private:
    Logger* logger = Logger::getInstance();
    std::string filepath;
    int width, height;
    std::vector<Color> pixels;

public:
    // Initialisation
    PpmImage(const std::string &filepath, int width, int height);
    ~PpmImage() override;

    // Image reading util function
    void read() override;
    Color getPixel(int x, int y) override;

    // Image writing util functions
    void setPixel(int x, int y, const Color &color) override;
    void write() override;
};


#endif //CGR_RAYTRACER_IMAGE_WRITER_H