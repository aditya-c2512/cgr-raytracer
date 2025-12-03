//
// Created by Aditya Choubey on 20/09/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_COLOR_H
#define CGR_RAYTRACER_COLOR_H
#include <string>

#include "camera.h"

class Color {
private:
    double red, green, blue;

public:
    Color() : red(0), green(0), blue(0) {}
    Color(double red, double green, double blue);

    double getRed() const;
    double getGreen() const;
    double getBlue() const;

    Color operator*(double x) const;

    Color operator+(const Color & color) const;

    Color operator*(const Color& other) const {
        return { red * other.red, green * other.green, blue * other.blue };
    }

    std::string toString() const;

    void clamp() {
        red = std::min(1.0, std::max(0.0, red));
        green = std::min(1.0, std::max(0.0, green));
        blue = std::min(1.0, std::max(0.0, blue));
    }

    Color operator/(double x) const {
        return {red/x, green/x, blue/x};
    }
};

#endif //CGR_RAYTRACER_COLOR_H