#ifndef IMAGE_H
#define IMAGE_H

#include <cassert>
#include <cstdint>
#include <vector>

#include "Math/Vec3.h"

enum class Channel { RED, GREEN, BLUE };

class PixelSpan {
  public:
    PixelSpan(std::vector<std::uint8_t>::iterator&& iter) : _iter{std::move(iter)} {}

    void set(int red, int green, int blue) {
        *_iter = red;
        *(_iter + 1) = green;
        *(_iter + 2) = blue;
    }

    void set(Color color) {
        *_iter = 255.999 * color.x();
        *(_iter + 1) = 255.999 * color.y();
        *(_iter + 2) = 255.999 * color.z();
    }

  private:
    std::vector<std::uint8_t>::iterator _iter;
};

class Image {
  public:
    Image(int width, int height) : _width{width}, _height{height}, _data(_width * _height * 3, 0) {}
    std::uint8_t* getData();
    std::uint8_t& operator()(int x, int y, Channel colorChannel);
    PixelSpan operator()(int x, int y);

  private:
    int _width;
    int _height;
    std::vector<std::uint8_t> _data;

    int getOffsetForColorComponent(Channel colorChannel);
};

#endif