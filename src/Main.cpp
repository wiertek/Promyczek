#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Image.h"
#include "Viewer/Viewer.h"

auto filename = "/home/piotr/repos/Promyczek/test.png";

int main(int argc, char* argv[]) {
    std::cout << "Świeć promyczku świeć!" << std::endl;

    const auto width = 512;
    const auto height = 512;

    Image testImage(width, height);

    for (int y = height - 1; y >= 0; y--) {
        std::cout << "Rows remaining: " << y << std::endl;
        for (int x = 0; x < width; x++) {
            Color pixelColor(static_cast<double>(x) / (width - 1), static_cast<double>(y) / (height - 1), 0.25);
            testImage(x, y).set(pixelColor);
        }
    }

    stbi_write_png(filename, width, height, 3, testImage.getData(), 0);
    // stbi_write_bmp("/home/piotr/repos/Promyczek/test.bmp", width, height, 3, testImage.getData());

    Viewer(filename, width, height).run();
}