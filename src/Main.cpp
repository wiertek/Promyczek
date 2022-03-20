#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

#include "Image.h"
#include "Math/Ray.h"
#include "Math/Utils.h"
#include "Math/Vec3.h"
#include "Model/Materials/Material.h"
#include "Model/Primitives/Collision.h"
#include "Model/Primitives/Sphere.h"
#include "Model/Scene.h"
#include "Model/World.h"
#include "Rendering/Camera.h"
#include "Rendering/Raytracer.h"
#include "Viewer/Viewer.h"

namespace {
CameraSettings cameraSettings{
    .lookFrom = Point3(13, 2, 3),
    .lookAt = Point3(0, 0, 0),
    .vecUp = Vec3(0, 1, 0),
    .verticalFov = 15.0,
};

RaytracerSettings raytracerSettings{
    .imageWidth = 1600,
    .imageHeight = 900,
    .maxRayDepth = 50,
    .gammaCorrection = 2.0,
    .samplesPerPixel = 100,
};

} // namespace

Scene generateScene(int imageWidth, int imageHeight) {
    cameraSettings.aspectRatio = static_cast<double>(imageWidth) / imageHeight;
    Camera camera(cameraSettings);

    World world;
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
                    albedo = Color::randomDelicateColor();
                    sphere_material = std::make_shared<Metal>(albedo, 0.0);
                    world.add(make_shared<Sphere>(center, 0.5, sphere_material));
                } else if (choose_mat < 0.95) {
                    // Metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    albedo = Color(1, 1, 1);
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

    return Scene(camera, world);
}

int main(int argc, char* argv[]) {
    std::cout << "Świeć promyczku świeć!" << std::endl;

    auto imagePath = "/home/piotr/repos/Promyczek/renders/test.png";
    if (argc == 2) {
        auto samplesPerPixel = std::atoi(argv[1]);
        if (samplesPerPixel == 0) {
            raytracerSettings.samplesPerPixel = 1;
        } else {
            raytracerSettings.samplesPerPixel = samplesPerPixel;
        }
    }
    auto scene = generateScene(raytracerSettings.imageWidth, raytracerSettings.imageHeight);

    Raytracer raytracer(raytracerSettings);
    raytracer.renderScene(scene, imagePath);
    Viewer(imagePath, raytracerSettings.imageWidth, raytracerSettings.imageHeight).run();

    return EXIT_SUCCESS;
}