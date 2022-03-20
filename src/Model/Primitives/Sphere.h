#ifndef SPHERE_H
#define SPHERE_H

#include <memory>
#include <optional>

#include "../../Math/Vec3.h"
#include "../Materials/Material.h"
#include "Collision.h"

class Sphere : public Primitive {
  public:
    Sphere() {}
    Sphere(Point3 center, double radius, std::shared_ptr<Material> material)
        : _center{center}, _radius{radius}, _material{material} {};

    virtual std::optional<Collision> hit(const Ray& ray, double tMin, double tMax) const override;

  private:
    Point3 _center;
    double _radius;
    std::shared_ptr<Material> _material;
};

#endif