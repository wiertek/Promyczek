#ifndef CAMERA_H
#define CAMERA_H

#include "../Common.h"
#include "../Math/Ray.h"
#include "../Math/Vec3.h"

class camera {
  public:
    camera(double verticalFov, // vertical field-of-view in degrees
           double aspectRatio) {
        auto theta = degreesToRadians(verticalFov);
        auto h = tan(theta / 2);
        auto viewportHeight = 2.0 * h;
        auto viewportHeight = aspectRatio * viewportHeight;

        auto focalLength = 1.0;
        origin = Point3(0, 0, 0);
        horizontal = Vec3(viewportHeight, 0.0, 0.0);
        vertical = Vec3(0.0, viewportHeight, 0.0);
        lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);
    }

    Ray getRay(double u, double v) const {
        return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
    }

  private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
};

#endif