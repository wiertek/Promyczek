#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Math/Ray.h"
#include "../Math/Vec3.h"

struct HitEvent;

class Material {
  public:
    virtual bool scatter(const Ray& inRay, const HitEvent& hitEvent, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
  public:
    Lambertian(const Color& color) : _albedo(color) {}

    virtual bool scatter(const Ray& inRay,
                         const HitEvent& hitEvent,
                         Color& attenuation,
                         Ray& scattered) const override {
        auto scatterDirection = unitVector(randomInHemisphere(hitEvent.normal));

        if (scatterDirection.isNearZero()) {
            scatterDirection = hitEvent.normal;
        }

        scattered = Ray(hitEvent.point, scatterDirection);
        attenuation = _albedo;
        return true;
    }

  private:
    Color _albedo;
};

class Metal : public Material {
  public:
    Metal(const Color& color, double fuzz) : _albedo(color), _fuzz(fuzz) {}

    virtual bool scatter(const Ray& inRay,
                         const HitEvent& hitEvent,
                         Color& attenuation,
                         Ray& scattered) const override {
        Vec3 directionReflected = reflect(unitVector(inRay.direction()), hitEvent.normal);
        scattered = Ray(hitEvent.point, directionReflected + _fuzz * randomInUnitSphere());
        attenuation = _albedo;
        return (dot(scattered.direction(), hitEvent.normal) > 0);
    }

  private:
    Color _albedo;
    double _fuzz;
};

class Dielectric : public Material {
  public:
    Dielectric(double refractionIndex) : _refractionIndex(refractionIndex) {}

    virtual bool scatter(const Ray& inRay,
                         const HitEvent& hitEvent,
                         Color& attenuation,
                         Ray& scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double refractionRatio = hitEvent.frontFace ? (1.0 / _refractionIndex) : _refractionIndex;

        Vec3 unitDirection = unitVector(inRay.direction());
        double cosTheta = fmin(dot(-unitDirection, hitEvent.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        Vec3 direction;

        if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble()) {
            direction = reflect(unitDirection, hitEvent.normal);
        } else {
            direction = refract(unitDirection, hitEvent.normal, refractionRatio);
        }

        scattered = Ray(hitEvent.point, direction);
        return true;
    }

  private:
    double _refractionIndex;

    static double reflectance(double cosTheta, double refractionRatio) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refractionRatio) / (1 + refractionRatio);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosTheta), 5);
    }
};

#endif