#include "HittableList.h"

bool HittableList::hit(const Ray& ray, double tMin, double tMax, HitEvent& hitEvent) const {
    HitEvent tempHitEvent;
    bool hitAnything = false;
    auto closestSoFar = tMax;

    for (const auto& object : objects) {
        if (object->hit(ray, tMin, closestSoFar, tempHitEvent)) {
            hitAnything = true;
            closestSoFar = tempHitEvent.t;
            hitEvent = tempHitEvent;
        }
    }

    return hitAnything;
}