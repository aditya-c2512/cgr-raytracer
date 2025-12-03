//
// Created by Aditya Choubey on 13/11/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_BLINN_PHONG_MATERIAL_H
#define CGR_RAYTRACER_BLINN_PHONG_MATERIAL_H
#include "material.h"
#include "math/utils.h"
#include "utils/ppm_image.h"
#include "utils/json/json_value.h"

class BlinnPhongMaterial: public Material {
private:
    Logger* logger = Logger::getInstance();

    PpmImage* texture = nullptr;
    Color diffuseAlbedo;
    double specularIntensity = 0.0;
    double shininess = 0.0;
    int dielectric = 0;

    LambertianMaterial lambertian;
    MetallicMaterial metallic;
    DielectricMaterial dielectricMaterial;

public:
    BlinnPhongMaterial() = default;
    explicit BlinnPhongMaterial(JsonObject& materialJson);
    ~BlinnPhongMaterial() override = default;

    bool scatter(const Ray &ray, const Hit &record, Color &attenuation,
        Ray &scatteredRay) const override;

    Color brdf(const Hit &hit, const Vec3 &wi, const Vec3 &wo) const override;

    bool isGlossy() const override { return specularIntensity > 0.0 && !dielectric; }

    Vec3 sampleGlossy(const Hit &hit, const Vec3 &wo, double &outPdf, const mathutils::RNG &rng) const override;

    bool isDielectric() const override {
        return dielectric;
    }

    double getShininess() const override {
        return shininess;
    }

    double getSpecularIntensity() const override {
        return specularIntensity;
    }
};

#endif //CGR_RAYTRACER_BLINN_PHONG_MATERIAL_H