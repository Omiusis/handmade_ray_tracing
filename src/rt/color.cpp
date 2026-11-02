#include "rt/color.h"

#include <algorithm>
#include <cstdint>
#include <cmath>

std::uint8_t rt::color_byte(double linear)
{
    double clamped= std::clamp(linear,0.0,1.0);
    double gamma_corrected = 255.99*std::sqrt(clamped);
    std::uint8_t color = static_cast<std::uint8_t>(gamma_corrected); 
    return color;
}

std::array<std::uint8_t,3> rt::color_to_RGB(const Color& temp)
{
    std::array<std::uint8_t,3> temp_RGB;
    temp_RGB.at(0)=color_byte(temp.x);
    temp_RGB.at(1)=color_byte(temp.y);
    temp_RGB.at(2)=color_byte(temp.z);

    return temp_RGB;
}
