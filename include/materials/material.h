//
// Created by Aditya Choubey on 13/11/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_MATERIAL_H
#define CGR_RAYTRACER_MATERIAL_H
#include "lights/light.h"
#include "math/color.h"
#include "math/ray.h"
#include "math/utils.h"
#include "shapes/shape.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& ray, const Hit& record, Color& attenuation, Ray& scatteredRay) const {
        return false;
    }

    virtual Color brdf(const Hit& hit, const Vec3& wi, const Vec3& wo) const {
        return {0, 0, 0};
    }

    virtual bool isGlossy() const {
        return false;
    }

    virtual Vec3 sampleGlossy(const Hit &hit, const Vec3 &wo, double &outPdf, const mathutils::RNG &rng) const {
        return {0, 0, 0};
    }

    virtual bool isDielectric() const {
        return false;
    }

    virtual double getShininess() const {
        return 0;
    }

    virtual double getSpecularIntensity() const {
        return 0;
    }
};

class LambertianMaterial: public Material {
private:
    Color albedo;
public:
    explicit LambertianMaterial() = default;
    explicit LambertianMaterial(const Color& albedo) : albedo(albedo) {}
    ~LambertianMaterial() override = default;

    bool scatter(const Ray &ray, const Hit &record, Color &attenuation, Ray &scatteredRay) const override {
        return false;
    }
};

class MetallicMaterial: public Material {
private:
    Color albedo;
    double specularIntensity{};

public:
    MetallicMaterial() = default;
    MetallicMaterial(const Color& albedo, const double& specularIntensity) : albedo(albedo), specularIntensity(specularIntensity) {}
    ~MetallicMaterial() override = default;

    bool scatter(const Ray &ray, const Hit &record, Color &attenuation, Ray &scatteredRay) const override {
        Vec3 reflectedDir = ray.getDirection().reflect(record.getNormal());
        scatteredRay = Ray(record.getPoint(), reflectedDir);
        attenuation = albedo;
        return true;
    }
};

class DielectricMaterial: public Material {
    private:
    Color albedo;
    double refractionIndex{};
public:
    DielectricMaterial() = default;
    DielectricMaterial(const Color& albedo, const double& refractionIndex): albedo(albedo), refractionIndex(refractionIndex) {}

    ~DielectricMaterial() override = default;

    bool scatter(const Ray &ray, const Hit &record, Color &attenuation, Ray &scatteredRay) const override {
        attenuation = albedo;
        double eta = record.getIsFrontFace() ? (1.0 / refractionIndex) : refractionIndex;

        Vec3 unitDir = ray.getDirection().normalize();
        double cosTheta = std::fmin(-unitDir.dot(record.getNormal()), 1.0);
        double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);

        Vec3 direction;
        if (eta * sinTheta > 1.0) {
            direction = unitDir.reflect(record.getNormal());
        }
        else {
            direction = unitDir.refract(record.getNormal(), eta);
        }

        scatteredRay = Ray(record.getPoint(), direction);
        return true;
    }
};

#endif //CGR_RAYTRACER_MATERIAL_H