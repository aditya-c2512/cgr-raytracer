//
// Created by Aditya Choubey on 08/10/2025.
//

#ifndef CGR_RAYTRACER_UTILS_H
#define CGR_RAYTRACER_UTILS_H
#include <random>

namespace mathutils{
    constexpr double PI = 3.1415926535897932385;

    inline double degreesToRadians(const double degrees) {
        return degrees * PI / 180.0;
    }

    inline double getRandom(double min, double max) {
        static std::random_device rd;
        static std::uniform_real_distribution<double> dist(min, max);
        return dist(rd);
    }

    struct RNG {
        mutable std::mt19937 gen;
        mutable std::uniform_real_distribution<double> uni;
        RNG(unsigned seed = std::random_device{}()) : gen(seed), uni(0.0, 1.0) {}
        double operator()() const { return uni(gen); } // returns in [0,1)
    };

    inline void makeBasis(const Vec3 &w, Vec3 &u, Vec3 &v) {
        Vec3 tmp = fabs(w.getX()) > 0.9 ? Vec3(0,1,0) : Vec3(1,0,0);
        u = tmp.cross(w).normalize();
        v = w.cross(u).normalize();
    }

    inline Vec3 samplePhongLobe(const Vec3 &axis, double exponent, const RNG &rng, double &outPdf) {
        double u1 = rng();
        double u2 = rng();
        double phi = 2.0 * M_PI * u1;
        // cosTheta distribution: cosTheta = u2^(1/(s+1))
        double cosTheta = pow(u2, 1.0 / (exponent + 1.0));
        double sinTheta = sqrt(std::max(0.0, 1.0 - cosTheta * cosTheta));
        double x = sinTheta * cos(phi);
        double y = sinTheta * sin(phi);
        double z = cosTheta; // local-space z

        // Create basis where z-axis = axis
        Vec3 tangent, bitangent;
        makeBasis(axis, tangent, bitangent);
        // transform local (x,y,z) to world: x*tangent + y*bitangent + z*axis
        Vec3 d = (tangent * x + bitangent * y + axis * z).normalize();

        // PDF of sampled direction (around axis) for Phong lobe
        outPdf = (exponent + 1.0) / (2.0 * M_PI) * pow(std::max(0.0, axis.dot(d)), exponent);
        return d;
    }
}

#endif //CGR_RAYTRACER_UTILS_H