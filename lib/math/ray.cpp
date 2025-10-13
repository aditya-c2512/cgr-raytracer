//
// Created by Aditya Choubey on 07/10/2025.
//

#include <fstream>
#include <math/ray.h>

Ray::Ray(): origin(0, 0, 0), direction(0, 0, 0) {
}

Ray::Ray(const Point3 &origin, const Vec3 &direction): origin(origin), direction(direction) {
}

Point3 Ray::getOrigin() const {
    return origin;
}

Vec3 Ray::getDirection() const {
    return direction;
}

Point3 Ray::at(const double t) const {
    return origin + direction * t;
}

void Ray::visualise(const std::string& filename) const {
    if (logger->getLogLevel() != LOG_LEVEL_DEBUG) {
        return;
    }

    std::ofstream file(filename, std::ios::app); // append mode
    if (!file.is_open()) {
        logger->error("Could not open file '" + filename + "' for writing.\n");
        return;
    }

    file << "Ray Origin: ("
         << origin.getX() << ", " << origin.getY() << ", " << origin.getZ() << ") "
         << "Direction: ("
         << direction.getX() << ", " << direction.getY() << ", " << direction.getZ() << ")\n";

    file.close();
}
