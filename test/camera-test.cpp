//
// Created by Aditya Choubey on 21/10/2025.
//
#include <gtest/gtest.h>
#include <cmath>
#include <math/camera.h>
#include <math/vec3.h>
#include <math/ray.h>
#include <utils/json/json.h>

const double EPS = 1e-9;

// Helper to compare Vec3s
testing::AssertionResult Vec3Near(const Vec3& a, const Vec3& b, double tol = EPS) {
    if (std::fabs(a.getX() - b.getX()) < tol &&
        std::fabs(a.getY() - b.getY()) < tol &&
        std::fabs(a.getZ() - b.getZ()) < tol)
        return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure() << "Expected " << b << " but got " << a;
}

static JsonObject makeCameraJson() {
    JsonObject obj;
    obj["location"] = JsonValue(JsonArray{JsonValue(0.0), JsonValue(0.0), JsonValue(0.0)});
    obj["gaze_direction"] = JsonValue(JsonArray{JsonValue(0.0), JsonValue(0.0), JsonValue(-1.0)});
    obj["focal_length_m"] = JsonValue(1.0);

    JsonObject filmResObj;
    filmResObj["x"] = JsonValue(3);
    filmResObj["y"] = JsonValue(3);
    obj["film_resolution"] = JsonValue(filmResObj);
    obj["vertical_fov"] = JsonValue(67.38013505195957),
    obj["horizontal_fov"] = JsonValue(90.0);
    obj["sensor_width_m"] = JsonValue(3.0);
    obj["sensor_height_m"] = JsonValue(3.0);
    return obj;
}

// ---------- Tests ----------
TEST(CameraTest, ConstructsCorrectlyFromJson) {
    JsonObject obj = makeCameraJson();
    Camera cam(obj);

    EXPECT_TRUE(Vec3Near(cam.getOrigin(), Vec3(0, 0, 0)));
    EXPECT_EQ(cam.getImageWidth(), 3);
    EXPECT_EQ(cam.getImageHeight(), 3);
}

TEST(CameraTest, GetRayFromCenterIsForward) {
    JsonObject obj = makeCameraJson();
    Camera cam(obj);

    // Middle pixel (2,1)
    Ray ray = cam.getRay(1, 1);
    Vec3 dir = ray.getDirection().normalize();

    EXPECT_NEAR(dir.dot(cam.getForward()), 1.0, 1e-6);
}

TEST(CameraTest, RaysAtCornersHaveDifferentDirections) {
    JsonObject obj = makeCameraJson();
    Camera cam(obj);

    Ray tl = cam.getRay(0, 0);
    Ray br = cam.getRay(3, 1);

    EXPECT_LT(tl.getDirection().getZ(), 0);
    EXPECT_LT(br.getDirection().getZ(), 0);
    EXPECT_LT(tl.getDirection().getX(), 0);
    EXPECT_GT(br.getDirection().getX(), 0);
}

TEST(CameraTest, RaysAreNormalized) {
    JsonObject obj = makeCameraJson();
    Camera cam(obj);

    Ray r = cam.getRay(1, 1);
    EXPECT_NEAR(r.getDirection().length(), 1.0, EPS);
}

TEST(CameraTest, getRayOriginMatchesCameraOrigin) {
    JsonObject obj = makeCameraJson();
    Camera cam(obj);

    for (int y = 0; y < cam.getImageHeight(); ++y) {
        for (int x = 0; x < cam.getImageWidth(); ++x) {
            Ray r = cam.getRay(x, y);
            EXPECT_TRUE(Vec3Near(r.getOrigin(), cam.getOrigin()));
        }
    }
}

TEST(CameraTest, AdjacentPixelRaysDiffer) {
    JsonObject obj = makeCameraJson();
    Camera cam(obj);

    Ray r1 = cam.getRay(0, 0);
    Ray r2 = cam.getRay(1, 0);
    EXPECT_GT((r2.getDirection() - r1.getDirection()).length(), 0.0);
}
