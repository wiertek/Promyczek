#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable {
  public:
    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) {
        add(object);
    }

    void clear() {
        objects.clear();
    }
    void add(std::shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    virtual bool hit(const Ray& ray, double tMin, double tMax, HitEvent& hitEvent) const override;

  public:
    std::vector<std::shared_ptr<Hittable>> objects;
};

#endif