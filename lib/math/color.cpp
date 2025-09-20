//
// Created by Aditya Choubey on 20/09/2025.
//

#include <math/color.h>

Color::Color(const double red, const double green, const double blue): red(red), green(green), blue(blue) {
}

double Color::getRed() const {
    return red;
}

double Color::getGreen() const {
    return green;
}

double Color::getBlue() const {
    return blue;
}
