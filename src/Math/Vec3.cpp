#include "Vec3.h"

Vec3 randomInUnitSphere() {
    while (true) {
        auto vec = Vec3::random(-1, 1);
        if (vec.lengthSquared() >= 1.0) {
            continue;
        }

        return vec;
    }
}

Vec3 randomUnitVector() {
    return unitVector(randomInUnitSphere());
}

Vec3 randomInHemisphere(const Vec3& normal) {
    Vec3 inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
        return inUnitSphere;
    else
        return -inUnitSphere;
}