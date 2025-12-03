//
// Created by Aditya Choubey on 25/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_BVH_H
#define CGR_RAYTRACER_BVH_H

#include <map>
#include <shapes/aabb.h>

#include <utility>

class BVHNode: public Shape {
private:
    Logger* logger = Logger::getInstance();
    BVHNode* left, *right;
    AxisAlignedBBox* bBox;
    Shape* shape = nullptr;

public:
    BVHNode(AxisAlignedBBox* bBox, BVHNode* left, BVHNode* right, Shape* shape)
        : left(left), right(right), bBox(bBox), shape(shape) {}
    ~BVHNode() {
        delete bBox;
        delete left;
        delete right;
    }

    BVHNode* getLeft() const { return left; }
    BVHNode* getRight() const { return right; }
    AxisAlignedBBox* getBBox() const { return bBox; }
    Shape* getShape() const { return shape; }

    bool intersect(const Ray &ray, double tMin, double tMax, Hit &record) override {
        if (bBox != nullptr) {
            Hit bboxHit;
            if (!bBox->intersect(ray, tMin, tMax, bboxHit)) {
                return false;
            }
        }

        bool hitAnything = false;

        if (shape != nullptr) {
            if (shape->intersect(ray, tMin, tMax, record)) {
                hitAnything = true;
                tMax = record.getT();
            }
        }

        if (left != nullptr) {
            if (left->intersect(ray, tMin, tMax, record)) {
                hitAnything = true;
                tMax = record.getT();
            }
        }

        if (right != nullptr) {
            if (right->intersect(ray, tMin, tMax, record)) {
                hitAnything = true;
                tMax = record.getT();
            }
        }

        return hitAnything;
    }

    bool occluded(const Ray& ray, double tMin, double tMax) const {
        if (bBox != nullptr) {
            Hit tmp;
            if (!bBox->intersect(ray, tMin, tMax, tmp)) {
                return false;
            }
        }

        if (shape != nullptr) {
            Hit tmp; // discarded
            if (shape->intersect(ray, tMin, tMax, tmp)) {
                return true;
            }
        }

        if (left && left->occluded(ray, tMin, tMax)) {
            return true;
        }
        if (right && right->occluded(ray, tMin, tMax)) {
            return true;
        }

        return false;
    }
};

class BoundingVolumeHierarchy {
private:
    std::vector<BVHNode*> roots;

public:
    BoundingVolumeHierarchy() = default;
    explicit BoundingVolumeHierarchy(JsonObject& bvhObject, const std::map<std::string, Shape*>& shapes) {
        JsonArray rootsArray = bvhObject["roots"].as<JsonArray>();
        for (auto& rootObj : rootsArray) {
            BVHNode* rootNode = buildNode(rootObj.as<JsonObject>(), shapes);
            if (rootNode != nullptr) {
                roots.push_back(rootNode);
            }
        }
    }

    BVHNode* buildNode(JsonObject nodeObj, const std::map<std::string, Shape*>& shapes) {
        if (nodeObj.size() == 0) return nullptr;

        double xMin = nodeObj["xMin"].as<double>();
        double xMax = nodeObj["xMax"].as<double>();
        double yMin = nodeObj["yMin"].as<double>();
        double yMax = nodeObj["yMax"].as<double>();
        double zMin = nodeObj["zMin"].as<double>();
        double zMax = nodeObj["zMax"].as<double>();

        AxisAlignedBBox* aabb = new AxisAlignedBBox(
            Vec3(xMin, yMin, zMin),
            Vec3(xMax, yMax, zMax)
        );

        Shape* shape = nullptr;
        if (nodeObj.contains("shape")) {
            std::string shapeName = nodeObj["shape"].as<std::string>();
            shape = shapes.at(shapeName);
        }

        JsonObject leftObj  = nodeObj["left"].as<JsonObject>();
        JsonObject rightObj = nodeObj["right"].as<JsonObject>();

        BVHNode* leftNode  = (leftObj.size()  > 0) ? buildNode(leftObj, shapes) : nullptr;
        BVHNode* rightNode = (rightObj.size() > 0) ? buildNode(rightObj, shapes) : nullptr;

        auto* node = new BVHNode(aabb, leftNode, rightNode, shape);
        return node;
    }
    ~BoundingVolumeHierarchy() {
        for (auto root : roots) delete root;
    }

    bool intersect(const Ray &ray, double tMin, double tMax, Hit &record) {
        for (auto root : roots) {
            if (root->intersect(ray, tMin, tMax, record)) {
                return true;
            }
        }
        return false;
    }

    bool occluded(const Ray& ray, double tMin, double tMax) const {
        for (auto root : roots) {
            if (root->occluded(ray, tMin, tMax)) {
                return true;
            }
        }
        return false;
    }

    std::vector<BVHNode*> getRoots() const { return roots; }
};

#endif //CGR_RAYTRACER_BVH_H