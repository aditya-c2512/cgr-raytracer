//
// Created by Aditya Choubey on 13/10/2025.
//

#ifndef CGR_RAYTRACER_LIGHT_H
#define CGR_RAYTRACER_LIGHT_H
#include <random>

#include "math/color.h"
#include "math/vec3.h"
#include "utils/json/json_value.h"

class Light {
public:
    virtual ~Light() {}

    virtual bool isArea() const = 0;

    virtual void sample(const Point3& surface, Point3& lightPoint, Vec3& lightNormal, Color& emitted, double& pdf) const = 0;
};

class PointLight: public Light {
private:
    Point3 position;
    Color color;
    double intensity;

public:
    PointLight(JsonObject& lightJson) {
        auto locationArray = lightJson["location"].as<JsonArray>();
        position = Point3(locationArray[0].as<double>(), locationArray[1].as<double>(), locationArray[2].as<double>());

        auto colorArray = lightJson["color"].as<JsonArray>();
        color = Color(colorArray[0].as<double>(), colorArray[1].as<double>(), colorArray[2].as<double>());

        intensity = lightJson["radiant_intensity"].as<double>();
    }

    bool isArea() const override { return false; }

    void sample(const Point3& surface, Point3& lightPoint, Vec3& lightNormal,
        Color& emitted, double& pdf) const override {
        lightPoint = position;
        lightNormal = Vec3(0,0,0);
        emitted = color * (intensity / 1000.0);
        pdf = 1.0;
    }

    Point3 getLocation() const { return position; }
    Color getColor() const { return color; }
    double getIntensity() const { return intensity; }
};

class RectLight : public Light {
public:
    Point3 center;
    Vec3 u, v;
    double width, height;
    Color emitted;

    mutable std::mt19937 rng {std::random_device{}()};
    mutable std::uniform_real_distribution<double> uni {0.0, 1.0};

    RectLight(JsonObject& obj) {
        auto c = obj["location"].as<JsonArray>();
        center = Point3(c[0].as<double>(), c[1].as<double>(), c[2].as<double>());

        auto uArr = obj["u"].as<JsonArray>();
        auto vArr = obj["v"].as<JsonArray>();
        u = Vec3(uArr[0].as<double>(), uArr[1].as<double>(), uArr[2].as<double>()).normalize();
        v = Vec3(vArr[0].as<double>(), vArr[1].as<double>(), vArr[2].as<double>()).normalize();

        width  = obj["width"].as<double>();
        height = obj["height"].as<double>();

        auto col = obj["color"].as<JsonArray>();
        emitted = Color(col[0].as<double>(), col[1].as<double>(), col[2].as<double>());
    }

    bool isArea() const override { return true; }

    void sample(const Point3& surface, Point3& lightPoint, Vec3& lightNormal,
        Color& Le, double& pdf) const override {
        double r1 = uni(rng) - 0.5;
        double r2 = uni(rng) - 0.5;

        lightPoint = center + u * (r1 * width) + v * (r2 * height);
        lightNormal = u.cross(v).normalize();
        Le = emitted;

        pdf = 1.0 / (width * height);
    }
};

#endif //CGR_RAYTRACER_LIGHT_H