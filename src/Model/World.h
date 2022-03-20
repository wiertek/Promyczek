#ifndef WORLD_H
#define WORLD_H

#include "Primitives/Collision.h"

#include <memory>
#include <optional>
#include <vector>

class World {
  public:
    World() {}
    World(std::shared_ptr<Primitive> object) {
        add(object);
    }

    void clear() {
        objects.clear();
    }
    void add(std::shared_ptr<Primitive> object) {
        objects.push_back(object);
    }

    std::optional<Collision> hit(const Ray& ray, double tMin, double tMax) const;

  public:
    std::vector<std::shared_ptr<Primitive>> objects;
};

#endif