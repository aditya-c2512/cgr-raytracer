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

Color Color::operator*(double x) const {
    return {red * x, green * x, blue * x};
}

Color Color::operator+(const Color &color) const {
    return {red + color.red, green + color.green, blue + color.blue};
}

std::string Color::toString() const {
    return "(" + std::to_string(red) + ", " + std::to_string(green) + ", " + std::to_string(blue) + ")";
}
