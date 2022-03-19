#ifndef WORLD_H
#define WORLD_H

#include "Hittable.h"

#include <memory>
#include <vector>

class World {
  public:
    World() {}
    World(std::shared_ptr<Hittable> object) {
        add(object);
    }

    void clear() {
        objects.clear();
    }
    void add(std::shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& ray, double tMin, double tMax, HitEvent& hitEvent) const;

  public:
    std::vector<std::shared_ptr<Hittable>> objects;
};

#endif