#ifndef CAMERA_H
#define CAMERA_H

#include "Math/Ray.h"
#include "Math/Vec3.h"

class Camera {
  private:
    const double focalLength{1.0};

  public:
    Camera(double viewportWidth, double viewportHeight) {
        _origin = Point3(0, 0, 0);
        _horizontal = Vec3(viewportWidth, 0.0, 0.0);
        _vertical = Vec3(0.0, viewportHeight, 0.0);
        _lower_left_corner = _origin - (_horizontal / 2) - (_vertical / 2) - Vec3(0, 0, focalLength);
    }

    Ray getRay(double u, double v) const {
        return Ray(_origin, _lower_left_corner + (u * _horizontal) + (v * _vertical) - _origin);
    }

  private:
    Point3 _origin;
    Point3 _lower_left_corner;
    Vec3 _horizontal;
    Vec3 _vertical;
};

#endif