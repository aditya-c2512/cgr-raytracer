//
// Created by Aditya Choubey on 25/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_BVH_H
#define CGR_RAYTRACER_BVH_H

#include <shapes/aabb.h>

#include <utility>

class BVHNode: public Shape {
private:
    BVHNode* left, *right;
    AxisAlignedBBox* bBox;
    Shape* shape;

public:
    BVHNode(AxisAlignedBBox* bBox, BVHNode* left, BVHNode* right, Shape* shape)
        : bBox(bBox), left(left), right(right), shape(shape) {}
    ~BVHNode() {
        delete bBox;
        delete shape;
        delete left;
        delete right;
    }

    BVHNode* getLeft() const { return left; }
    BVHNode* getRight() const { return right; }
    AxisAlignedBBox* getBBox() const { return bBox; }
    Shape* getShape() const { return shape; }

    bool intersect(const Ray &ray, double tMin, double tMax, Hit &record) override {
        if (bBox != nullptr && bBox->intersect(ray, tMin, tMax, record)) {
            if (shape != nullptr && shape->intersect(ray, tMin, tMax, record)) {
                return true;
            }
            if (left != nullptr && left->intersect(ray, tMin, tMax, record)) {
                return true;
            }
            if (right != nullptr && right->intersect(ray, tMin, tMax, record)) {
                return true;
            }
        }

        return false;
    }
};

class BoundingVolumeHierarchy {
private:
    std::vector<BVHNode*> roots;

public:
    BoundingVolumeHierarchy() = default;
    explicit BoundingVolumeHierarchy(std::vector<BVHNode*> roots): roots(std::move(roots)) {}
    ~BoundingVolumeHierarchy() {
        for (auto root : roots) delete root;
    }

    std::vector<BVHNode*> getRoots() const { return roots; }
};

#endif //CGR_RAYTRACER_BVH_H