//
// Created by Aditya Choubey on 07/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_IMAGE_H
#define CGR_RAYTRACER_IMAGE_H

#include <vector>
#include <math/color.h>

class Image {
public:
    virtual ~Image() = default;
    virtual void read() = 0;
    virtual void write() = 0;
    virtual void setPixel(int x, int y, const Color& color) = 0;
    virtual Color getPixel(int x, int y) = 0;
};

#endif //CGR_RAYTRACER_IMAGE_H