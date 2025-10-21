//
// Created by Aditya Choubey on 21/10/2025.
//
#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include <math/vec3.h>

// Utility epsilon for floating-point comparison
const double EPS = 1e-9;

// Helper function for comparing Vec3 values
testing::AssertionResult vec3Near(const Vec3& a, const Vec3& b, double tol = EPS) {
    if (std::fabs(a.getX() - b.getX()) < tol &&
        std::fabs(a.getY() - b.getY()) < tol &&
        std::fabs(a.getZ() - b.getZ()) < tol)
        return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure() << "Expected " << b << " but got " << a;
}

// ---------- Constructors ----------
TEST(Vec3Test, DefaultConstructorInitializesToZero) {
    Vec3 v;
    EXPECT_DOUBLE_EQ(v.getX(), 0);
    EXPECT_DOUBLE_EQ(v.getY(), 0);
    EXPECT_DOUBLE_EQ(v.getZ(), 0);
}

TEST(Vec3Test, ParameterizedConstructorSetsValues) {
    Vec3 v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
}

TEST(Vec3Test, CopyConstructorCopiesValues) {
    Vec3 a(1, 2, 3);
    Vec3 b(a);
    EXPECT_TRUE(vec3Near(a, b));
}

// ---------- Operator Index ----------
TEST(Vec3Test, IndexOperatorAccessesComponents) {
    Vec3 v(10, 20, 30);
    EXPECT_DOUBLE_EQ(v[0], 10);
    EXPECT_DOUBLE_EQ(v[1], 20);
    EXPECT_DOUBLE_EQ(v[2], 30);
}

TEST(Vec3Test, IndexOperatorThrowsOutOfRange) {
    Vec3 v(1, 2, 3);
    EXPECT_THROW(v[3], std::out_of_range);
    EXPECT_THROW(v[-1], std::out_of_range);
}

// ---------- Arithmetic Operators ----------
TEST(Vec3Test, UnaryMinusNegatesComponents) {
    Vec3 v(1, -2, 3);
    Vec3 expected(-1, 2, -3);
    EXPECT_TRUE(vec3Near(-v, expected));
}

TEST(Vec3Test, AdditionOperatorWorks) {
    Vec3 a(1, 2, 3), b(4, 5, 6);
    EXPECT_TRUE(vec3Near(a + b, Vec3(5, 7, 9)));
}

TEST(Vec3Test, SubtractionOperatorWorks) {
    Vec3 a(4, 5, 6), b(1, 2, 3);
    EXPECT_TRUE(vec3Near(a - b, Vec3(3, 3, 3)));
}

TEST(Vec3Test, ElementWiseMultiplicationWorks) {
    Vec3 a(1, 2, 3), b(2, 3, 4);
    EXPECT_TRUE(vec3Near(a * b, Vec3(2, 6, 12)));
}

TEST(Vec3Test, ElementWiseDivisionWorks) {
    Vec3 a(2, 6, 12), b(2, 3, 4);
    EXPECT_TRUE(vec3Near(a / b, Vec3(1, 2, 3)));
}

TEST(Vec3Test, ScalarMultiplicationWorks) {
    Vec3 a(1, 2, 3);
    EXPECT_TRUE(vec3Near(a * 2.0, Vec3(2, 4, 6)));
}

TEST(Vec3Test, ScalarDivisionWorks) {
    Vec3 a(2, 4, 6);
    EXPECT_TRUE(vec3Near(a / 2.0, Vec3(1, 2, 3)));
}

// ---------- Compound Assignment ----------
TEST(Vec3Test, CompoundAdditionWorks) {
    Vec3 a(1, 2, 3);
    a += Vec3(2, 3, 4);
    EXPECT_TRUE(vec3Near(a, Vec3(3, 5, 7)));
}

TEST(Vec3Test, CompoundMultiplicationWorks) {
    Vec3 a(1, 2, 3);
    a *= 2;
    EXPECT_TRUE(vec3Near(a, Vec3(2, 4, 6)));
}

TEST(Vec3Test, CompoundDivisionWorks) {
    Vec3 a(2, 4, 6);
    a /= 2;
    EXPECT_TRUE(vec3Near(a, Vec3(1, 2, 3)));
}

// ---------- Vector Math ----------
TEST(Vec3Test, LengthAndLengthSquaredAreCorrect) {
    Vec3 a(3, 4, 12);
    EXPECT_DOUBLE_EQ(a.lengthSquared(), 9 + 16 + 144);
    EXPECT_DOUBLE_EQ(a.length(), 13);
}

TEST(Vec3Test, DotProductWorks) {
    Vec3 a(1, 2, 3), b(4, -5, 6);
    EXPECT_DOUBLE_EQ(a.dot(b), 1*4 + 2*(-5) + 3*6);
}

TEST(Vec3Test, CrossProductWorks) {
    Vec3 a(1, 0, 0), b(0, 1, 0);
    EXPECT_TRUE(vec3Near(a.cross(b), Vec3(0, 0, 1)));
}

TEST(Vec3Test, NormalizeWorks) {
    Vec3 a(3, 0, 4);
    Vec3 n = a.normalize();
    EXPECT_NEAR(n.length(), 1.0, EPS);
    EXPECT_TRUE(vec3Near(n, Vec3(0.6, 0.0, 0.8)));
}

TEST(Vec3Test, NormalizeZeroVectorReturnsZeroOrNaNHandled) {
    Vec3 zero(0, 0, 0);
    Vec3 n = zero.normalize();
    // Accept either zero or safe NaN handling depending on implementation
    EXPECT_TRUE(std::isfinite(n.getX()) || n.getX() == 0);
    EXPECT_TRUE(std::isfinite(n.getY()) || n.getY() == 0);
    EXPECT_TRUE(std::isfinite(n.getZ()) || n.getZ() == 0);
}

// ---------- Stream Operator ----------
TEST(Vec3Test, OutputStreamFormatsCorrectly) {
    Vec3 v(1, 2, 3);
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "(1, 2, 3)");
}
