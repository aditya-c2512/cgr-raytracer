//
// Created by Aditya Choubey on 20/10/2025.
//
#pragma once

#ifndef CGR_RAYTRACER_MATRIX3X3_H
#define CGR_RAYTRACER_MATRIX3X3_H
#include <math/vec3.h>

class Matrix3x3 {
public:
    double m[3][3];

    Matrix3x3() {
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
                m[i][j] = 0.0;
    }

    Matrix3x3(std::initializer_list<std::initializer_list<double>> list) {
        int i = 0;
        for (auto& row : list) {
            int j = 0;
            for (auto& val : row) {
                if (i < 3 && j < 3)
                    m[i][j] = val;
                j++;
            }
            i++;
        }
    }

    static Matrix3x3 identity() {
        Matrix3x3 I;
        for (int i=0;i<3;i++) I.m[i][i] = 1.0;
        return I;
    }

    static Matrix3x3 rotationFromEulerZYX(const Vec3& euler) {
        double cr = std::cos(euler.getX()), sr = std::sin(euler.getX());
        double cp = std::cos(euler.getY()), sp = std::sin(euler.getY());
        double cy = std::cos(euler.getZ()), sy = std::sin(euler.getZ());

        Matrix3x3 Rz ={{
                { cy, -sy, 0 },
                { sy,  cy, 0 },
                {  0,   0, 1 }
        }};
        Matrix3x3 Ry = {{
            {  cp, 0, sp },
            {   0, 1,  0 },
            { -sp, 0, cp }
        }};
        Matrix3x3 Rx = {{
            { 1,   0,    0 },
            { 0,  cr, -sr },
            { 0,  sr,  cr }
        }};
        return Rz * Ry * Rx;
    }

    Matrix3x3 operator*(const Matrix3x3& o) const {
        Matrix3x3 r;
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
                for (int k=0;k<3;k++)
                    r.m[i][j] += m[i][k]*o.m[k][j];
        return r;
    }

    Vec3 operator*(const Vec3& v) const {
        return {
            m[0][0]*v.getX() + m[0][1]*v.getY() + m[0][2]*v.getZ(),
            m[1][0]*v.getX() + m[1][1]*v.getY() + m[1][2]*v.getZ(),
            m[2][0]*v.getX() + m[2][1]*v.getY() + m[2][2]*v.getZ()
        };
    }

    Matrix3x3 abs() const {
        Matrix3x3 r;
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
                r.m[i][j] = std::fabs(m[i][j]);
        return r;
    }
};

#endif //CGR_RAYTRACER_MATRIX3X3_H