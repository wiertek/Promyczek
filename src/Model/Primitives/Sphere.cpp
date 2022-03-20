#include "Sphere.h"

std::optional<Collision> Sphere::hit(const Ray& ray, double tMin, double tMax) const {
    Vec3 oc = ray.origin() - _center;
    auto a = ray.direction().lengthSquared();
    auto half_b = dot(oc, ray.direction());
    auto c = oc.lengthSquared() - _radius * _radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
        return std::nullopt;
    }
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < tMin || tMax < root) {
        root = (-half_b + sqrtd) / a;
        if (root < tMin || tMax < root) {
            return std::nullopt;
        }
    }
    auto t = root;
    auto point = ray.at(t);
    auto normal = (point - _center) / _radius;
    Vec3 outwardNormal = (point - _center) / _radius;
    auto frontFace = dot(ray.direction(), outwardNormal) < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;

    return Collision(point, normal, t, frontFace, _material);
}