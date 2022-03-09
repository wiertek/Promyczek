#include "Image.h"
#include <iostream>

std::uint8_t* Image::getData() {
    return _data.data();
}

std::uint8_t& Image::operator()(int x, int y, Channel colorChannel) {
    auto index = (_height - 1 - y) * (_width * 3) + (x * 3) + getOffsetForColorComponent(colorChannel);
    // std::cout << "settting " << std::to_string(index) << " for " << std::to_string(x) << "," << std::to_string(y)
    //           << std::endl;
    return _data[index];
}

PixelSpan Image::operator()(int x, int y) {
    auto index = (_height - 1 - y) * (_width * 3) + (x * 3);
    return PixelSpan(_data.begin() + index);
}

int Image::getOffsetForColorComponent(Channel colorChannel) {
    switch (colorChannel) {
        case Channel::RED: return 0;
        case Channel::GREEN: return 1;
        case Channel::BLUE: return 2;
    }
}