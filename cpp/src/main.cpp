#include "gli/texture2d.hpp"
#include <iostream>

#include <gli/gli.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

int main() {
    gli::texture tex = gli::load("/Users/loneil/Repositories/pygli/build-debug/_deps/gli-src/data/kueken7_rgba8_unorm.dds");
    assert(!tex.empty());
    auto format = tex.format();
    auto extent = tex.extent();
    std::cout << extent.x << ", " << extent.y << ", " << 4 << std::endl;
    stbi_write_png("output.png", extent.x, extent.y, 4, tex.data(), extent.x * 4);
    return 0;
}