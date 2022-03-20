#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <string>

#include "../Math/Vec3.h"
#include "../Model/Scene.h"

struct RaytracerSettings {
    int imageWidth;
    int imageHeight;
    int maxRayDepth;
    double gammaCorrection;
    int samplesPerPixel;
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