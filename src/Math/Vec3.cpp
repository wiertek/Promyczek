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

Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dot(v, n) * n;
}

Vec3 refract(const Vec3& uv, const Vec3& n, double etaiOverEtat) {
    auto cosTheta = fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp = etaiOverEtat * (uv + cosTheta * n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.lengthSquared())) * n;
    return r_out_perp + r_out_parallel;
}