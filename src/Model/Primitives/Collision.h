#ifndef COLLISION_H
#define COLLISION_H

#include <memory>
#include <optional>
#include <utility>

#include "../../Math/Ray.h"
#include "../../Math/Vec3.h"

class Material;

struct Collision {
  public:
    Collision(Point3 pointArg, Vec3 normalArg, double tArg, bool frontFaceArg, std::shared_ptr<Material> materialArg)
        : point{pointArg}, normal{normalArg}, t{tArg}, frontFace{frontFaceArg}, material{materialArg} {}

    Point3 point;
    Vec3 normal;
    double t;
    bool frontFace;
    std::shared_ptr<Material> material;
};

class Primitive {
  public:
    virtual std::optional<Collision> hit(const Ray& ray, double tMin, double tMax) const = 0;
};

#endif