#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <cstddef>

namespace rt
{

    class image
    {
    private:
        size_t m_width;
        size_t m_height;
        std::vector<uint8_t> pixel_data;
    public:

        image(size_t width_,size_t height_);
        ~image();

        size_t width() const;
        size_t height() const;

        void set_pixel(int x,int y,std::uint8_t R,std::uint8_t G,std::uint8_t B);//x,y are 0-based

        bool saved_as_bmp(const std::string& path_,std::string* error =nullptr) const;
        bool saved_as_ppm(const std::string& path_,std::string* error =nullptr) const;
    };
    

    

}


