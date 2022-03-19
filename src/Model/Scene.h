#ifndef SCENE_H
#define SCENE_H

#include "../Rendering/Camera.h"
#include "World.h"

class Scene {
  public:
    Scene(Camera camera, World world) : _camera{camera}, _world{world} {}
    const Camera& getCamera() const {
        return _camera;
    }
    const World& getWorld() const {
        return _world;
    }

  private:
    Camera _camera;
    World _world;
};

#endif