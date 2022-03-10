#ifndef SPHERE_H
#define SPHERE_H

#include "../Math/Vec3.h"
#include "Hittable.h"

class Sphere : public Hittable {
  public:
    Sphere() {}
    Sphere(Point3 center, double radius) : _center(center), _radius(radius){};

    virtual bool hit(const Ray& ray, double tMin, double tMax, HitEvent& hitEvent) const override;

  public:
    Point3 _center;
    double _radius;
};

#endif