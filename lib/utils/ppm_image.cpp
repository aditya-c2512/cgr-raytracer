//
// Created by Aditya Choubey on 19/09/2025.
//

#include <utils/ppm_image.h>
#include <utils/logger.h>
#include <fstream>

PpmImage::PpmImage(const int width, const int height): width(width), height(height) {
    pixels.reserve(width * height);
}

PpmImage::~PpmImage() = default;

void PpmImage::setPixel(const int x, const int y, const Color &color) {
    pixels[y * width + x] = color;
    logger->debug("Set pixel (" + std::to_string(x) + ", " + std::to_string(y) +
    ") to R:" + std::to_string(color.getRed()) + ", G:" + std::to_string(color.getGreen()) + ", B:" + std::to_string(color.getBlue()));
}

void PpmImage::writeFile(const std::string& fileName) const {
    std::ofstream imageFile(fileName);

    if (!imageFile.is_open()) {
        logger->error("Unable to open file: " + fileName);
        return;
    }

    logger->info("Starting writing image to file: " + fileName);

    imageFile << "P3\n" << width << " " << height << "\n255\n";

    for (int i = 0; i < width * height; i++) {
        const int imageRed = static_cast<int>(255.999 * pixels[i].getRed());
        const int imageGreen = static_cast<int>(255.999 * pixels[i].getGreen());
        const int imageBlue = static_cast<int>(255.999 * pixels[i].getBlue());

        imageFile << imageRed << " " << imageGreen << " " << imageBlue << "\n";
    }

    logger->info("Finished writing image to file: " + fileName);
    imageFile.close();
}
