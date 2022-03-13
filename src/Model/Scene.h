#ifndef SCENE_H
#define SCENE_H

#include "../Rendering/Camera.h"
#include "HittableList.h"

class Scene {
  public:
    Scene(Camera camera, HittableList world) : _camera{camera}, _world{world} {}
    const Camera& getCamera() const {
        return _camera;
    }
    const HittableList& getWorld() const {
        return _world;
    }

  private:
    Camera _camera;
    HittableList _world;
};

#endif