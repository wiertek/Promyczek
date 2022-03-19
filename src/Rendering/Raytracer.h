#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <string>

#include "../Math/Vec3.h"
#include "../Model/Scene.h"

struct RaytracerSettings {
    int imageWidth{1600};
    int imageHeight{900};
    bool antialiasingEnabled = false;
    int antialiasSamplesPerPixel{500};
    int maxRayDepth{50};
    double gammaCorrection{2.0};
    double verticalFovDegrees{20.0};
};

class Raytracer {
  public:
    Raytracer(RaytracerSettings settings) : _settings{settings} {}
    void renderScene(const Scene& scene, const std::string& outputFile);

  private:
    Color shadeRay(const Ray& ray, const World& world, int depth);
    RaytracerSettings _settings;
};

#endif