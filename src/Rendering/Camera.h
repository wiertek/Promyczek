#ifndef CAMERA_H
#define CAMERA_H

#include "../Math/Ray.h"
#include "../Math/Utils.h"
#include "../Math/Vec3.h"

/*
  Contains information about camera position, orientation, defocus blur etc...

  Casts ray from camera to given "pixel"
*/
class Camera {
  private:
    const double focalLength{1.0};

  public:
    Camera(Point3 lookFrom,
           Point3 lookAt,
           Vec3 vecUp,
           double verticalFov,
           double aspectRatio,
           double aperture,
           double focusDist) {
        auto theta = degreesToRadians(verticalFov);
        auto h = tan(theta / 2);
        auto viewportHeight = 2.0 * h;
        auto viewportWidth = aspectRatio * viewportHeight;

        _w = unitVector(lookFrom - lookAt);
        _u = unitVector(cross(vecUp, _w));
        _v = cross(_w, _u);

        _origin = lookFrom;
        _horizontal = focusDist * viewportWidth * _u;
        _vertical = focusDist * viewportHeight * _v;
        _lowerLeftCorner = _origin - (_horizontal / 2) - (_vertical / 2) - (focusDist * _w);
        _lensRadius = aperture / 2;
    }

    Ray getRay(double u, double v) const {
        Vec3 rd = _lensRadius * randomInUnitDisk();
        Vec3 offset = _u * rd.x() + _v * rd.y();
        return Ray(_origin + offset, _lowerLeftCorner + (u * _horizontal) + (v * _vertical) - _origin - offset);
    }

  private:
    Point3 _origin;
    Point3 _lowerLeftCorner;
    Vec3 _horizontal;
    Vec3 _vertical;
    Vec3 _w, _u, _v; // vectors from camera position
    double _lensRadius;
};

#endif