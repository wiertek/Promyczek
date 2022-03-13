#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include "Image.h"
#include "Math/Ray.h"
#include "Math/Utils.h"
#include "Math/Vec3.h"
#include "Model/Hittable.h"
#include "Model/HittableList.h"
#include "Model/Material.h"
#include "Model/Scene.h"
#include "Model/Sphere.h"
#include "Rendering/Camera.h"
#include "Rendering/Raytracer.h"
#include "Viewer/Viewer.h"

Scene generateScene(const RaytracerSettings& settings) {
    const auto aspectRatio = static_cast<double>(settings.imageWidth) / settings.imageHeight;
    Point3 lookFrom(13, 2, 3);
    Point3 lookAt(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto distToFocus = 10;
    auto aperture = 0.1;
    Camera camera(lookFrom, lookAt, vup, settings.verticalFovDegrees, aspectRatio, aperture, distToFocus);

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

    return Scene(camera, world);
}

int main(int argc, char* argv[]) {
    std::cout << "Świeć promyczku świeć!" << std::endl;

    auto imagePath = "/home/piotr/repos/Promyczek/renders/test.png";
    RaytracerSettings settings;
    auto scene = generateScene(settings);

    Raytracer raytracer(settings);
    raytracer.renderScene(scene, imagePath);
    Viewer(imagePath, settings.imageWidth, settings.imageHeight).run();

    return EXIT_SUCCESS;
}