#pragma once

#include <array>
#include <cstdint>

#include "rt/vec3.h"

namespace rt
{
    std::uint8_t color_byte(double linear);
    std::array<uint8_t,3> color_to_RGB(const Color& temp);
}