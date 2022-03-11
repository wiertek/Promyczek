#include "Sphere.h"

bool Sphere::hit(const Ray& ray, double tMin, double tMax, HitEvent& hitEvent) const {
    Vec3 oc = ray.origin() - _center;
    auto a = ray.direction().lengthSquared();
    auto half_b = dot(oc, ray.direction());
    auto c = oc.lengthSquared() - _radius * _radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < tMin || tMax < root) {
        root = (-half_b + sqrtd) / a;
        if (root < tMin || tMax < root) {
            return false;
        }
    }
    hitEvent.t = root;
    hitEvent.point = ray.at(hitEvent.t);
    hitEvent.normal = (hitEvent.point - _center) / _radius;
    Vec3 outwardNormal = (hitEvent.point - _center) / _radius;
    hitEvent.setFaceNormal(ray, outwardNormal);
    return true;
}