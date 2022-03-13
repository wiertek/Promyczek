#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Common.h"
#include "Image.h"
#include "Math/Ray.h"
#include "Math/Vec3.h"
#include "Model/Hittable.h"
#include "Model/HittableList.h"
#include "Model/Material.h"
#include "Model/Sphere.h"
#include "Rendering/Camera.h"
#include "Viewer/Viewer.h"

auto filename = "/home/piotr/repos/Promyczek/renders/test.png";

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
const auto ANTIALIAS_SAMPLES_PER_PIXEL = 500;
const auto MAX_RAY_DEPTH = 50;
const auto GAMMA_CORRECTION = 2.0;
const auto VERTICAL_FOV_DEGREES = 20.0;

} // namespace Settings

HittableList random_scene() {
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomDouble();
            Point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // Metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

int main(int argc, char* argv[]) {
    std::cout << "Świeć promyczku świeć!" << std::endl;

    // Image
    const auto imageWidth = 1600;
    const auto imageHeight = 900;
    const auto aspectRatio = static_cast<double>(imageWidth) / static_cast<double>(imageHeight);

    // Camera
    Point3 lookFrom(13, 2, 3);
    Point3 lookAt(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto distToFocus = 10;
    auto aperture = 0.0;
    Camera camera(lookFrom, lookAt, vup, Settings::VERTICAL_FOV_DEGREES, aspectRatio, aperture, distToFocus);

    Image testImage(imageWidth, imageHeight);

    auto world = random_scene();

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