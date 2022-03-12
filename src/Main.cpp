#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Camera.h"
#include "Common.h"
#include "Image.h"
#include "Math/Ray.h"
#include "Math/Vec3.h"
#include "Model/Hittable.h"
#include "Model/HittableList.h"
#include "Model/Material.h"
#include "Model/Sphere.h"
#include "Viewer/Viewer.h"

auto filename = "/home/piotr/repos/Promyczek/test.png";

Color rayColor(const Ray& ray, const Hittable& world, int depth) {
    if (depth <= 0) {
        return Color(0, 0, 0);
    }

    HitEvent hitEvent;
    if (world.hit(ray, 0.001, Consts::Infinity, hitEvent)) {

        Ray scattered;
        Color attenuation;
        if (hitEvent.material->scatter(ray, hitEvent, attenuation, scattered)) {
            return attenuation * rayColor(scattered, world, depth - 1);
        }
        return Color(0, 0, 0);
    }
    Vec3 unitDirection = unitVector(ray.direction());
    auto t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

namespace Settings {

const bool ANTIALIASING_ENABLED = true;
const auto ANTIALIAS_SAMPLES_PER_PIXEL = 100;
const auto MAX_RAY_DEPTH = 50;
const auto GAMMA_CORRECTION = 2.0;

} // namespace Settings

int main(int argc, char* argv[]) {
    std::cout << "Świeć promyczku świeć!" << std::endl;

    // Image
    const auto imageWidth = 1600;
    const auto imageHeight = 900;
    const auto aspectRatio = static_cast<double>(imageWidth) / static_cast<double>(imageHeight);

    // Camera
    auto viewportHeight = 2.0; // <-1, 1>
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewportWidth, 0, 0); // horizontal edge
    auto vertical = Vec3(0, viewportHeight, 0);  // vertical full edge
    auto lowerLeftCorner = origin - (horizontal / 2) - (vertical / 2) - Vec3(0, 0, focal_length);

    Camera camera(viewportWidth, viewportHeight);

    Image testImage(imageWidth, imageHeight);

    // World
    HittableList world;
    auto material_ground = std::make_shared<Lambertian>(Color(16 / 255.0, 145.0 / 255.0, 12 / 255.0));
    auto material_center = std::make_shared<Lambertian>(Color(251.0 / 255, 0.0, 1.0));
    // auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    auto material_right = std::make_shared<Metal>(Color(10 / 255.0, 214 / 255.0, 1.0), 1.0);
    auto material_left = std::make_shared<Dielectric>(1.5);

    world.add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

    for (int y = imageHeight - 1; y >= 0; y--) {
        std::cout << "Rows remaining: " << y << std::endl;
        for (int x = 0; x < imageWidth; x++) {
            auto samplesCount = Settings::ANTIALIAS_SAMPLES_PER_PIXEL;
            if (!Settings::ANTIALIASING_ENABLED) {
                samplesCount = 1;
            }
            Color accumulatedPixelColor(0.0, 0.0, 0.0);
            for (auto i{0}; i < samplesCount; i++) {
                auto u = double(x + randomDouble()) / (imageWidth - 1);  // x in <0,1> range
                auto v = double(y + randomDouble()) / (imageHeight - 1); // y in <0,1> range
                auto ray = camera.getRay(u, v);
                accumulatedPixelColor += rayColor(ray, world, Settings::MAX_RAY_DEPTH);
            }
            auto pixelColor = Color(std::pow(accumulatedPixelColor.x() / static_cast<double>(samplesCount),
                                             1.0 / Settings::GAMMA_CORRECTION),
                                    std::pow(accumulatedPixelColor.y() / static_cast<double>(samplesCount),
                                             1.0 / Settings::GAMMA_CORRECTION),
                                    std::pow(accumulatedPixelColor.z() / static_cast<double>(samplesCount),
                                             1.0 / Settings::GAMMA_CORRECTION));

            testImage(x, y) = pixelColor;
        }
    }

    stbi_write_png(filename, imageWidth, imageHeight, 3, testImage.getData(), 0);

    Viewer(filename, imageWidth, imageHeight).run();
}