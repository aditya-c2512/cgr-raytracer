//
// Created by Aditya Choubey on 19/09/2025.
//

#include <utils/ppm_image.h>
#include <utils/logger.h>
#include <fstream>

PpmImage::PpmImage(const std::string &filepath, const int width, const int height): width(width), height(height) {
    this->filepath = filepath;
    pixels.reserve(width * height);
}

PpmImage::~PpmImage() = default;

void PpmImage::read() {
    std::ifstream imageFile(filepath, std::ios::binary);

    if (!imageFile.is_open()) {
        logger->error("Unable to open file: " + filepath);
        return;
    }

    logger->info("Reading image from file: " + filepath);

    std::string magicNumber;
    imageFile >> magicNumber;

    if (magicNumber != "P3") {
        logger->error("Unsupported PPM format: " + magicNumber);
        return;
    }

    char ch;
    imageFile >> std::ws;
    while (imageFile.peek() == '#') {
        std::string comment;
        std::getline(imageFile, comment);
        imageFile >> std::ws;
    }

    int tempWidth, tempHeight;
    imageFile >> tempWidth >> tempHeight;
    int maxColorValue;
    imageFile >> maxColorValue;
    imageFile.get(ch); // consume the newline after maxColorValue

    if (maxColorValue != 255) {
        logger->error("Only max color value 255 is supported.\n");
        return;
    }

    pixels.reserve(tempWidth * tempHeight);
    for (int i = 0; i < tempWidth * tempHeight; ++i) {
        int r, g, b;
        imageFile >> r >> g >> b;
        pixels[i] = Color(r/255.0, g/255.0, b/255.0);
    }
}

Color PpmImage::getPixel(int x, int y) {
    return pixels[y * width + x];
}

void PpmImage::setPixel(const int x, const int y, const Color &color) {
    pixels[y * width + x] = convertToGamma(color);
    // logger->debug("Set pixel (" + std::to_string(x) + ", " + std::to_string(y) +
    // ") to R:" + std::to_string(color.getRed()) + ", G:" + std::to_string(color.getGreen())
    // + ", B:" + std::to_string(color.getBlue()));
}

void PpmImage::write() {
    std::ofstream imageFile(filepath);

    if (!imageFile.is_open()) {
        logger->error("Unable to open file: " + filepath);
        return;
    }

    logger->info("Starting writing image to file: " + filepath);

    imageFile << "P3\n" << width << " " << height << "\n255\n";

    for (int i = 0; i < width * height; i++) {
        pixels[i].clamp();

        const int imageRed = static_cast<int>(255.999 * pixels[i].getRed());
        const int imageGreen = static_cast<int>(255.999 * pixels[i].getGreen());
        const int imageBlue = static_cast<int>(255.999 * pixels[i].getBlue());

        imageFile << imageRed << " " << imageGreen << " " << imageBlue << "\n";
    }

    const std::filesystem::path filePath(filepath);
    logger->info("Finished writing image to file: " + std::filesystem::absolute(filePath).string());
    imageFile.close();
}

double PpmImage::convertToGamma(const double value) {
    if (value < 0.0) return 0.0;

    return std::sqrt(value);
}

Color PpmImage::convertToGamma(const Color &color) {
    return {convertToGamma(color.getRed()), convertToGamma(color.getGreen()), convertToGamma(color.getBlue())};
}
