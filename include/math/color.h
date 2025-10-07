//
// Created by Aditya Choubey on 20/09/2025.
//

#pragma once

#ifndef CGR_RAYTRACER_COLOR_H
#define CGR_RAYTRACER_COLOR_H

class Color {
private:
    double red, green, blue;

public:
    Color(double red, double green, double blue);

    double getRed() const;
    double getGreen() const;
    double getBlue() const;

    Color operator*(double x) const;

    Color operator+(const Color & color) const;
};

#endif //CGR_RAYTRACER_COLOR_H