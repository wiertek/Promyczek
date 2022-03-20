#include "World.h"

std::optional<Collision> World::hit(const Ray& ray, double tMin, double tMax) const {
    // Collision tempHitEvent;
    bool hitAnything = false;
    auto closestSoFar = tMax;

    std::optional<Collision> hitEvent;
    for (const auto& object : objects) {
        if (auto tempHitEvent = object->hit(ray, tMin, closestSoFar); tempHitEvent) {
            hitAnything = true;
            closestSoFar = tempHitEvent->t;
            hitEvent = tempHitEvent.value();
        }
    }

    return hitEvent;
}