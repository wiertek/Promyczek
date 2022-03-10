#ifndef HITTABLE_H
#define HITTABLE_H

#include <utility>

#include "../Math/Ray.h"
#include "../Math/Vec3.h"

struct HitEvent {
    Point3 point;
    Vec3 normal;
    double t;
    bool front_face;

    inline void setFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
        front_face = dot(ray.direction(), outwardNormal) < 0;
        normal = front_face ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
  public:
    virtual bool hit(const Ray& ray, double tMin, double tMax, HitEvent& hitEvent) const = 0;
};

#endif