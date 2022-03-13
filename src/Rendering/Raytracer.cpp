

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "../Image.h"
#include "../Model/Material.h"
#include "Raytracer.h"

Color Raytracer::shadeRay(const Ray& ray, const Hittable& world, int depth) {
    if (depth <= 0) {
        return Color(0, 0, 0);
    }

    HitEvent hitEvent;
    if (world.hit(ray, 0.001, Consts::Infinity, hitEvent)) {

        Ray scattered;
        Color attenuation;
        if (hitEvent.material->scatter(ray, hitEvent, attenuation, scattered)) {
            return attenuation * shadeRay(scattered, world, depth - 1);
        }
        return Color(0, 0, 0);
    }
    Vec3 unitDirection = unitVector(ray.direction());
    auto t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

void Raytracer::renderScene(const Scene& scene, const std::string& outputFile) {

    Image outputImage(_settings.imageWidth, _settings.imageHeight);

    for (int row = _settings.imageHeight - 1; row >= 0; row--) {
        std::cout << "Rows remaining: " << row << std::endl;
        for (int col = 0; col < _settings.imageWidth; col++) {
            auto samplesCount = _settings.antialiasSamplesPerPixel;
            if (!_settings.antialiasingEnabled) {
                samplesCount = 1;
            }
            Color accumulatedPixelColor(0.0, 0.0, 0.0);
            for (auto i{0}; i < samplesCount; i++) {
                auto u = double(col + randomDouble()) / (_settings.imageWidth - 1);  // col in <0,1> range
                auto v = double(row + randomDouble()) / (_settings.imageHeight - 1); // row in <0,1> range
                auto ray = scene.getCamera().getRay(u, v);
                accumulatedPixelColor += shadeRay(ray, scene.getWorld(), _settings.maxRayDepth);
            }
            auto pixelColor =
                Color(std::pow(accumulatedPixelColor.x() / samplesCount, 1.0 / _settings.gammaCorrection),
                      std::pow(accumulatedPixelColor.y() / samplesCount, 1.0 / _settings.gammaCorrection),
                      std::pow(accumulatedPixelColor.z() / samplesCount, 1.0 / _settings.gammaCorrection));

            outputImage(col, row) = pixelColor;
        }
    }

    stbi_write_png(outputFile.data(), _settings.imageWidth, _settings.imageHeight, 3, outputImage.getData(), 0);
}