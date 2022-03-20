#ifndef CAMERA_H
#define CAMERA_H

#include <optional>

#include "../Math/Ray.h"
#include "../Math/Utils.h"
#include "../Math/Vec3.h"

/*
  Contains information about camera position, orientation, defocus blur etc...

  Casts ray from camera to given "pixel"
*/

struct DefocusBlurSettings {
    double aperture;
    double focusDist;
};

struct CameraSettings {
    Point3 lookFrom;
    Point3 lookAt;
    Vec3 vecUp;
    double verticalFov;
    double aspectRatio;
    std::optional<DefocusBlurSettings> defocusBlurSettings;
};

class Camera {
  private:
    const double focalLength{1.0};

  public:
    Camera(CameraSettings settings) {
        auto theta = degreesToRadians(settings.verticalFov);
        auto h = tan(theta / 2);
        auto viewportHeight = 2.0 * h;
        auto viewportWidth = settings.aspectRatio * viewportHeight;

        _w = unitVector(settings.lookFrom - settings.lookAt);
        _u = unitVector(cross(settings.vecUp, _w));
        _v = cross(_w, _u);

        _origin = settings.lookFrom;
        if (settings.defocusBlurSettings) {
            auto focusDist = settings.defocusBlurSettings->focusDist;
            auto aperture = settings.defocusBlurSettings->aperture;
            _horizontal = focusDist * viewportWidth * _u;
            _vertical = focusDist * viewportHeight * _v;
            _lowerLeftCorner = _origin - (_horizontal / 2) - (_vertical / 2) - (focusDist * _w);
            _lensRadius = aperture / 2;
        } else {
            _horizontal = viewportWidth * _u;
            _vertical = viewportHeight * _v;
            _lowerLeftCorner = _origin - (_horizontal / 2) - (_vertical / 2) - _w;
        }
    }

    Ray getRay(double u, double v) const {
        if (_lensRadius) {
            Vec3 rd = _lensRadius.value() * randomInUnitDisk();
            Vec3 offset = _u * rd.x() + _v * rd.y();
            return Ray(_origin + offset, _lowerLeftCorner + (u * _horizontal) + (v * _vertical) - _origin - offset);
        } else {
            return Ray(_origin, _lowerLeftCorner + (u * _horizontal) + (v * _vertical) - _origin);
        }
    }

  private:
    Point3 _origin;
    Point3 _lowerLeftCorner;
    Vec3 _horizontal;
    Vec3 _vertical;
    Vec3 _w, _u, _v; // vectors from camera position
    std::optional<double> _lensRadius;
};

#endif