//
// Created by Aditya Choubey on 21/10/2025.
//
#include <gtest/gtest.h>
#include <cmath>
#include <math/matrix3x3.h>
#include <math/vec3.h>

const double EPS = 1e-9;

// Helper comparison function for matrices
testing::AssertionResult matrixNear(const Matrix3x3& A, const Matrix3x3& B, double tol = EPS) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (std::fabs(A.m[i][j] - B.m[i][j]) > tol) {
                return ::testing::AssertionFailure()
                       << "Mismatch at (" << i << "," << j << "): "
                       << A.m[i][j] << " != " << B.m[i][j];
            }
        }
    }
    return ::testing::AssertionSuccess();
}

// ---------- Constructors ----------
TEST(Matrix3x3Test, DefaultConstructorSetsAllZero) {
    Matrix3x3 M;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_DOUBLE_EQ(M.m[i][j], 0.0);
}

TEST(Matrix3x3Test, InitializerListSetsCorrectValues) {
    Matrix3x3 M = {{ {1,2,3}, {4,5,6}, {7,8,9} }};
    EXPECT_DOUBLE_EQ(M.m[0][0], 1);
    EXPECT_DOUBLE_EQ(M.m[1][1], 5);
    EXPECT_DOUBLE_EQ(M.m[2][2], 9);
    EXPECT_DOUBLE_EQ(M.m[0][2], 3);
}

// ---------- Identity ----------
TEST(Matrix3x3Test, IdentityMatrixHasOnesOnDiagonal) {
    Matrix3x3 I = Matrix3x3::identity();
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_DOUBLE_EQ(I.m[i][j], (i == j ? 1.0 : 0.0));
}

// ---------- Matrix Multiplication ----------
TEST(Matrix3x3Test, MatrixMultiplicationProducesExpectedResult) {
    Matrix3x3 A = {{ {1,2,3}, {4,5,6}, {7,8,9} }};
    Matrix3x3 B = {{ {9,8,7}, {6,5,4}, {3,2,1} }};
    Matrix3x3 C = A * B;

    Matrix3x3 expected = {{
        { 1*9 + 2*6 + 3*3, 1*8 + 2*5 + 3*2, 1*7 + 2*4 + 3*1 },
        { 4*9 + 5*6 + 6*3, 4*8 + 5*5 + 6*2, 4*7 + 5*4 + 6*1 },
        { 7*9 + 8*6 + 9*3, 7*8 + 8*5 + 9*2, 7*7 + 8*4 + 9*1 }
    }};
    EXPECT_TRUE(matrixNear(C, expected));
}

// ---------- Matrix * Vector ----------
TEST(Matrix3x3Test, MatrixVectorMultiplicationIsCorrect) {
    Matrix3x3 M = {{ {1,2,3}, {4,5,6}, {7,8,9} }};
    Vec3 v(1, 2, 3);
    Vec3 r = M * v;
    EXPECT_NEAR(r.getX(), 1*1 + 2*2 + 3*3, EPS);
    EXPECT_NEAR(r.getY(), 4*1 + 5*2 + 6*3, EPS);
    EXPECT_NEAR(r.getZ(), 7*1 + 8*2 + 9*3, EPS);
}

// ---------- Abs Function ----------
TEST(Matrix3x3Test, AbsReturnsMatrixWithAbsoluteValues) {
    Matrix3x3 M = {{ {-1, 2, -3}, {4, -5, 6}, {-7, 8, -9} }};
    Matrix3x3 R = M.abs();
    EXPECT_TRUE(matrixNear(R, {{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} }}));
}

// ---------- RotationFromEulerZYX ----------
TEST(Matrix3x3Test, RotationFromEulerZYXZeroAngleGivesIdentity) {
    Vec3 euler(0, 0, 0);
    Matrix3x3 R = Matrix3x3::rotationFromEulerZYX(euler);
    EXPECT_TRUE(matrixNear(R, Matrix3x3::identity()));
}

TEST(Matrix3x3Test, RotationFromEulerZYXYaw90DegreesRotatesAroundZ) {
    Vec3 euler(0, 0, M_PI/2.0); // roll=0, pitch=0, yaw=90°
    Matrix3x3 R = Matrix3x3::rotationFromEulerZYX(euler);
    Vec3 v(1, 0, 0);
    Vec3 r = R * v;
    // Expected rotation around Z: (1,0,0) → (0,1,0)
    EXPECT_NEAR(r.getX(), 0.0, EPS);
    EXPECT_NEAR(r.getY(), 1.0, EPS);
    EXPECT_NEAR(r.getZ(), 0.0, EPS);
}

TEST(Matrix3x3Test, RotationFromEulerZYXPitch90DegreesRotatesAroundY) {
    Vec3 euler(0, M_PI/2.0, 0); // roll=0, pitch=90°, yaw=0
    Matrix3x3 R = Matrix3x3::rotationFromEulerZYX(euler);
    Vec3 v(0, 0, 1);
    Vec3 r = R * v;
    // Expected rotation around Y: (0,0,1) → (1,0,0)
    EXPECT_NEAR(r.getX(), 1.0, EPS);
    EXPECT_NEAR(r.getY(), 0.0, EPS);
    EXPECT_NEAR(r.getZ(), 0.0, EPS);
}

TEST(Matrix3x3Test, RotationFromEulerZYXRoll90DegreesRotatesAroundX) {
    Vec3 euler(M_PI/2.0, 0, 0); // roll=90°, pitch=0, yaw=0
    Matrix3x3 R = Matrix3x3::rotationFromEulerZYX(euler);
    Vec3 v(0, 1, 0);
    Vec3 r = R * v;
    // Expected rotation around X: (0,1,0) → (0,0,1)
    EXPECT_NEAR(r.getX(), 0.0, EPS);
    EXPECT_NEAR(r.getY(), 0.0, EPS);
    EXPECT_NEAR(r.getZ(), 1.0, EPS);
}