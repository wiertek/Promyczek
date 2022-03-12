#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "../Math/Vec3.h"
#include "Hittable.h"
#include "Material.h"

class Sphere : public Hittable {
  public:
    Sphere() {}
    Sphere(Point3 center, double radius, std::shared_ptr<Material> material)
        : _center{center}, _radius{radius}, _material{material} {};

    virtual bool hit(const Ray& ray, double tMin, double tMax, HitEvent& hitEvent) const override;

  private:
    Point3 _center;
    double _radius;
    std::shared_ptr<Material> _material;
};

#endif