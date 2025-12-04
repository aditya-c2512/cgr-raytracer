//
// Created by Aditya Choubey on 13/11/2025.
//
#include <materials/blinn-phong-material.h>

BlinnPhongMaterial::BlinnPhongMaterial(JsonObject &materialJson) {
    auto texturePath = materialJson["texture_path"].as<std::string>();
    if (texturePath.empty()) {
        const auto diffuseColorArray = materialJson["diffuse_color"].as<JsonArray>();
        diffuseAlbedo = Color(diffuseColorArray[0].as<double>(), diffuseColorArray[1].as<double>(),
                             diffuseColorArray[2].as<double>());
    }
    else {
        texture = new PpmImage(texturePath, TX, TY);
        texture->read();
    }

    specularIntensity = materialJson["specular_intensity"].as<double>();
    shininess = materialJson["shininess"].as<double>();
    dielectric = materialJson["is_dielectric"].as<int>();
    if (dielectric == 1) {
        try {
            dielectricMaterial = DielectricMaterial(Color(1.0, 1.0, 1.0),
                materialJson["refraction_index"].as<double>());
        }
        catch (...) {
            logger->error("Material was set to dielectric but material properties not found in JSON object.");
        }
    }

    lambertian = LambertianMaterial(diffuseAlbedo);
    metallic = MetallicMaterial(diffuseAlbedo, specularIntensity);
}

bool BlinnPhongMaterial::scatter(const Ray &ray, const Hit &record, Color &attenuation, Ray &scatteredRay) const {
    if (dielectric == 1) {
        Color dielectricAttenuation;
        Ray dielectricScatter;
        if (dielectricMaterial.scatter(ray, record, dielectricAttenuation, dielectricScatter)) {
            attenuation = dielectricAttenuation;
            scatteredRay = dielectricScatter;
            return true;
        }
        return false;
    }
    if (specularIntensity > 0.0) {
        Color metallicAttenuation;
        Ray metallicScatter;
        if (metallic.scatter(ray, record, metallicAttenuation, metallicScatter)) {
            attenuation = metallicAttenuation;
            scatteredRay = metallicScatter;
            return true;
        }
        return false;
    }

    return false;
}

Color BlinnPhongMaterial::brdf(const Hit &hit, const Vec3 &wi, const Vec3 &wo) const {
    Vec3 N = hit.getNormal();
    Vec3 H = (wi + wo).normalize();

    double NdotL = std::max(0.0, N.dot(wi));
    double NdotH = std::max(0.0, N.dot(H));

    int u = std::min(int(hit.getU() * (TX - 1)), TX - 1);
    int v = std::min(int(hit.getV() * (TY - 1)), TY - 1);
    Color baseColor = (texture == nullptr)
        ? diffuseAlbedo
        : texture->getPixel(u, v);

    Color diffuse  = baseColor * (1.0 / M_PI) * NdotL;
    Color specular = Color(1,1,1) * specularIntensity * pow(NdotH, shininess);

    return diffuse + specular;
}

Vec3 BlinnPhongMaterial::sampleGlossy(const Hit &hit, const Vec3 &wo, double &outPdf, const mathutils::RNG &rng) const {
    Vec3 N = hit.getNormal();
    Vec3 V = -wo;
    Vec3 R = V.reflect(N).normalize();

    double exponent = std::max(1.0, shininess);

    Vec3 sampledDir = mathutils::samplePhongLobe(R, exponent, rng, outPdf);

    if (sampledDir.dot(N) < 0.0) {
        sampledDir = (sampledDir - N * 2.0 * sampledDir.dot(N)).normalize();
    }
    return sampledDir;
}
