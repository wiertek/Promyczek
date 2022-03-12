#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>
#include <utility>

#include "../Math/Ray.h"
#include "../Math/Vec3.h"

class Material;

struct HitEvent {
    Point3 point;
    Vec3 normal;
    double t;
    bool frontFace;
    std::shared_ptr<Material> material;

    inline void setFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
        frontFace = dot(ray.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
  public:
    virtual bool hit(const Ray& ray, double tMin, double tMax, HitEvent& hitEvent) const = 0;
};

#endif