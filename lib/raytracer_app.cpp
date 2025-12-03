//
// Created by Aditya Choubey on 19/09/2025.
//

#include <ranges>
#include <raytracer_app.h>
#include <thread>
#include <utils/logger.h>
#include <math/ray.h>

#include "materials/material.h"

RayTracerApp::RayTracerApp(Scene* scene, const std::string& filepath, const int& maxDepth, const int& lightSamples,
    const int& glossySamples, int numThreads): scene(scene), maxDepth(maxDepth), lightSamples(lightSamples),
    glossySamples(glossySamples), numThreads(numThreads) {
    image = new PpmImage(filepath, scene->getCamera()->getImageWidth(), scene->getCamera()->getImageHeight());
}

RayTracerApp::~RayTracerApp() {
    delete image;
}

Color RayTracerApp::trace(const Ray& ray, int renderDepth) const {
    auto shapes = scene->getShapes();
    auto bvh = scene->getBVH();
    auto lights = scene->getLights();
    Color color;

    const Vec3 unitDirection = ray.getDirection().normalize();
    auto a = 0.5 * (unitDirection.getY() + 1.0);
    color = Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;

    double minT = std::numeric_limits<double>::max();;
    if (scene->canAccelerate()) {
        for (const auto bvhRoot: bvh->getRoots()) {
            Hit record;
            if (bvhRoot->intersect(ray, 0.001, 500000, record)) {
                if (record.getT() < minT) {
                    minT = record.getT();

                    Color hitColor(0.0, 0.0, 0.0);

                    for (auto &light : lights) {
                        for (int s = 0; s < lightSamples; s++) {
                            Point3 Lpos;
                            Vec3 Lnormal;
                            Color Le;
                            double pdf;

                            light->sample(record.getPoint(), Lpos, Lnormal, Le, pdf);

                            Vec3 wi = Lpos - record.getPoint().normalize();
                            double dist = (Lpos - record.getPoint()).length();

                            // Shadow ray
                            Ray shadowRay(record.getPoint() + record.getNormal() * 1e-5, wi);
                            double maxDist = (Lpos - record.getPoint()).length();

                            bool inShadow = bvh->occluded(shadowRay, 1e-4, 500000);

                            if (!inShadow) {
                                Vec3 wo = (ray.getOrigin() - record.getPoint()).normalize();
                                Color brdf = record.getMaterial()->brdf(record, wi, wo);

                                double NdotL = std::max(0.0, record.getNormal().dot(wi));

                                hitColor = hitColor + brdf * Le * NdotL / (pdf * dist * dist);
                            }
                        }
                    }

                    hitColor = hitColor / lightSamples;

                    // After you compute hitColor from direct lighting and before assigning color = hitColor:
                    if (renderDepth > 0) {
                        // check if material wants dielectrics / metals handled by existing scatter()
                        Ray scattered;
                        Color attenuation;
                        if (record.getMaterial()->isDielectric()) {
                            if (record.getMaterial()->scatter(ray, record, attenuation, scattered)) {
                                hitColor = hitColor + attenuation * trace(scattered, renderDepth - 1);
                            }
                        }
                        else if (record.getMaterial()->isGlossy()) {
                            // Distributed glossy sampling
                            Color glossyAccum(0.0, 0.0, 0.0);
                            // outgoing vector from surface to camera
                            Vec3 wo = (ray.getOrigin() - record.getPoint()).normalize();

                            for (int g = 0; g < glossySamples; ++g) {
                                double pdf;
                                Vec3 sampledDir = record.getMaterial()->sampleGlossy(record, wo, pdf, rng);

                                // spawn reflection ray
                                Ray refl(record.getPoint() + record.getNormal() * 0.001, sampledDir);

                                // trace recursively
                                Color Li = trace(refl, renderDepth - 1);

                                // weight by cosine term and BRDF factor:
                                // we already sampled according to Phong pdf p(omega)
                                // use a simple Monte Carlo estimator: (specularTerm * Li * cos(N,wi)) / p
                                double cosNwi = std::max(0.0, record.getNormal().dot(sampledDir));

                                // Specular BRDF factor (Phong): ks * (s+2)/(2π) * cos^s
                                // With sampling PDF p = (s+1)/(2π) * cos^s  => ratio simplifies roughly to ks * (s+2)/(s+1) * (2π cancel)
                                // For a practical and stable estimator we use the following:
                                double s = std::max(1.0, record.getMaterial()->getShininess());
                                double ks = record.getMaterial()->getSpecularIntensity();

                                // Compute a simple weight: ks * cosNwi / pdf
                                // (This is a pragmatic estimator; you may substitute the exact BRDF/pdfs if you want)
                                double weight = (pdf > 0.0) ? (ks * cosNwi / pdf) : 0.0;

                                glossyAccum = glossyAccum + Li * weight;
                            }

                            // average glossy contribution
                            glossyAccum = glossyAccum / static_cast<double>(glossySamples);

                            // Add to hit color
                            hitColor = hitColor + glossyAccum;
                        }
                        else {
                            // Non-glossy diffuse / no recursion
                            if (record.getMaterial()->scatter(ray, record, attenuation, scattered)) {
                                hitColor = hitColor + attenuation * trace(scattered, renderDepth - 1);
                            }
                        }
                    }

                    color = hitColor;
                }
            }
        }
    }
    else {
        for (auto shape: shapes | std::views::values) {
            Hit record;
            if (shape->intersect(ray, 0.001, 500000, record)) {
                if (record.getT() < minT) {
                    minT = record.getT();

                    Color hitColor(0.0, 0.0, 0.0);

                    for (auto &light : lights) {
                        for (int s = 0; s < lightSamples; s++) {
                            Point3 Lpos;
                            Vec3 Lnormal;
                            Color Le;
                            double pdf;

                            light->sample(record.getPoint(), Lpos, Lnormal, Le, pdf);

                            Vec3 wi = Lpos - record.getPoint().normalize();
                            double dist = (Lpos - record.getPoint()).length();

                            // Shadow ray
                            Ray shadow(record.getPoint() + record.getNormal() * 0.001, wi);
                            Hit shadowHit;
                            bool hitShadow = false;
                            for (auto shadowShape: shapes | std::views::values) {
                                if (shadowShape->intersect(shadow, 0.001, dist, shadowHit)) {
                                    hitShadow = true;
                                }
                            }
                            if (!hitShadow) {
                                Vec3 wo = (ray.getOrigin() - record.getPoint()).normalize();
                                Color brdf = record.getMaterial()->brdf(record, wi, wo);

                                double NdotL = std::max(0.0, record.getNormal().dot(wi));

                                hitColor = hitColor + brdf * Le * NdotL / (pdf * dist * dist);
                            }
                        }
                    }

                    hitColor = hitColor / lightSamples;

                    // After you compute hitColor from direct lighting and before assigning color = hitColor:
                    if (renderDepth > 0) {
                        // check if material wants dielectrics / metals handled by existing scatter()
                        Ray scattered;
                        Color attenuation;
                        if (record.getMaterial()->isDielectric()) {
                            if (record.getMaterial()->scatter(ray, record, attenuation, scattered)) {
                                hitColor = hitColor + attenuation * trace(scattered, renderDepth - 1);
                            }
                        }
                        else if (record.getMaterial()->isGlossy()) {
                            // Distributed glossy sampling
                            Color glossyAccum(0.0, 0.0, 0.0);
                            // outgoing vector from surface to camera
                            Vec3 wo = (ray.getOrigin() - record.getPoint()).normalize();

                            for (int g = 0; g < glossySamples; ++g) {
                                double pdf;
                                Vec3 sampledDir = record.getMaterial()->sampleGlossy(record, wo, pdf, rng);

                                // spawn reflection ray
                                Ray refl(record.getPoint() + record.getNormal() * 0.001, sampledDir);

                                // trace recursively
                                Color Li = trace(refl, renderDepth - 1);

                                // weight by cosine term and BRDF factor:
                                // we already sampled according to Phong pdf p(omega)
                                // use a simple Monte Carlo estimator: (specularTerm * Li * cos(N,wi)) / p
                                double cosNwi = std::max(0.0, record.getNormal().dot(sampledDir));

                                // Specular BRDF factor (Phong): ks * (s+2)/(2π) * cos^s
                                // With sampling PDF p = (s+1)/(2π) * cos^s  => ratio simplifies roughly to ks * (s+2)/(s+1) * (2π cancel)
                                // For a practical and stable estimator we use the following:
                                double s = std::max(1.0, record.getMaterial()->getShininess());
                                double ks = record.getMaterial()->getSpecularIntensity();

                                // Compute a simple weight: ks * cosNwi / pdf
                                // (This is a pragmatic estimator; you may substitute the exact BRDF/pdfs if you want)
                                double weight = (pdf > 0.0) ? (ks * cosNwi / pdf) : 0.0;

                                glossyAccum = glossyAccum + Li * weight;
                            }

                            // average glossy contribution
                            glossyAccum = glossyAccum / glossySamples;

                            // Add to hit color
                            hitColor = hitColor + glossyAccum;
                        }
                        else {
                            // Non-glossy diffuse / no recursion
                            if (record.getMaterial()->scatter(ray, record, attenuation, scattered)) {
                                hitColor = hitColor + attenuation * trace(scattered, renderDepth - 1);
                            }
                        }
                    }

                    color = hitColor;
                }
            }
        }
    }

    // logger->debug("Intersection point at ray " + std::to_string(minT));
    return color;
}

// void RayTracerApp::run() const {
//     logger->info("Starting up Raytracer App.");
//
//     Camera* camera = scene->getCamera();
//
//     logger->info("Starting Rendering Stage");
//
//     for (int y = 0; y < camera->getImageHeight(); y++) {
//         for (int x = 0; x < camera->getImageWidth(); x++) {
//             Color pixelColor = {};
//             auto samplesPerPixel = camera->getSamplesPerPixel();
//
//             for (int sample = 0; sample < samplesPerPixel; sample++) {
//                 Ray ray = camera->getRay(x, y);
//                 pixelColor = pixelColor + trace(ray, maxDepth);
//             }
//
//             pixelColor = pixelColor / samplesPerPixel;
//             // logger->debug("Color for pixel (" + std::to_string(x) + ", " + std::to_string(y) + "): " + pixelColor.toString());
//             image->setPixel(x, y, pixelColor);
//         }
//
//         logger->info("Rendered Scanline #" + std::to_string(y+1));
//     }
//
//     logger->info("Finished Rendering Stage");
//
//     image->write();
//
//     logger->info("Finished up Raytracer App.");
// }

void RayTracerApp::run() const {
    logger->info("Starting up Raytracer App.");

    Camera* camera = scene->getCamera();
    const int width = camera->getImageWidth();
    const int height = camera->getImageHeight();
    const int samplesPerPixel = camera->getSamplesPerPixel();

    logger->info("Starting Rendering Stage");

    std::atomic<int> nextScanline{0}; // a thread-safe counter

    // Worker code: claim scanlines dynamically
    auto worker = [&]() {
        while (true) {
            int y = nextScanline.fetch_add(1);
            if (y >= height) return;

            for (int x = 0; x < width; ++x) {
                Color pixelColor{0,0,0};
                for (int s = 0; s < samplesPerPixel; ++s) {
                    Ray ray = camera->getRay(x, y);
                    pixelColor = pixelColor + trace(ray, maxDepth);
                }
                pixelColor = pixelColor / double(samplesPerPixel);
                image->setPixel(x, y, pixelColor);
            }

            logger->info("Rendered Scanline #" + std::to_string(y + 1));
        }
    };

    // Launch threads
    std::vector<std::thread> workers;
    workers.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i) {
        workers.emplace_back(worker);
    }

    // Wait for completion
    for (auto &t : workers) t.join();

    logger->info("Finished Rendering Stage");

    image->write();
    logger->info("Finished up Raytracer App.");
}
