#include "rt/image.h"

#include <cstdint>
#include <string>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
rt::image::image(size_t width_,size_t height_)
{
    if(width_==0) throw std::invalid_argument("Image width can not be zero");
    if (height_==0) throw std::invalid_argument("Image height can not be zero");
    if(width_>std::numeric_limits<size_t>::max()/height_) throw std::invalid_argument("width is too large or negative");
    rt::image::m_width=width_;

    if(height_>std::numeric_limits<size_t>::max()/width_) throw std::invalid_argument("height is too large or negative");
    rt::image::m_height=height_;
    if(width_*height_ > std::numeric_limits<size_t>::max()/3) throw std::invalid_argument("The total memory image requied overflows ");
    rt::image::pixel_data.resize(m_width * m_height * 3);
}

rt::image::~image()
{}
size_t rt::image::width()const
{
    return m_width;
}

size_t rt::image::height()const
{
    return m_height;
}

void rt::image::set_pixel(int x,int y,std::uint8_t R,std::uint8_t G,std::uint8_t B)
{
    size_t index;
    if(x<0) throw std::invalid_argument("set_pixel : int x <=0");
    if(y<0) throw std::invalid_argument("set_pixel : int y <=0");

    index= (static_cast<size_t>(y)*width()+static_cast<size_t>(x))*3;

    pixel_data.at(index)=R;
    pixel_data.at(index+1)=G;
    pixel_data.at(index+2)=B;
}

namespace rt
{
    inline void write_2b(std::ostream& os,std::uint16_t in)
    {
        const std::uint8_t ready[2] = 
        {
            static_cast<std::uint8_t>(in&0xff),
            static_cast<std::uint8_t>((in>>8)&0xff)
        };

        os.write(reinterpret_cast<const char *>(ready),2);
    }

    inline void write_4b(std::ostream& os,std::uint32_t in)
    {
        const std::uint8_t ready[4] = 
        {
            static_cast<std::uint8_t>(in&0xff),
            static_cast<std::uint8_t>((in>>8)&0xff),
            static_cast<std::uint8_t>((in>>16)&0xff),
            static_cast<std::uint8_t>((in>>24)&0xff)
        };

        os.write(reinterpret_cast<const char *>(ready),4);
    }
}

bool rt::image::saved_as_bmp(const std::string& path_,std::string* error ) const
{

    time_t now = time(0);
    std::ofstream write_bmp;
    if(now==-1) throw std::runtime_error("can`t get system time");
    std::string path=path_+std::to_string(now)+".bmp";

    write_bmp.open(path,std::ios::out | std::ios::binary);
    if (!write_bmp.is_open())
    {
        throw std::runtime_error("can not open the file");
    }

    //File Header
    write_2b(write_bmp,0x4D42);//BM
    size_t padding = (4 - (width()*3) % 4)%4;
    size_t size= (padding+width()*3)*height()+54;
    if(size>=std::numeric_limits<uint32_t>::max()) throw std::runtime_error("size is larger than .bmp requied");
    write_4b(write_bmp,static_cast<uint32_t>(size));
    write_2b(write_bmp,0x0000);
    write_2b(write_bmp,0x0000);
    write_4b(write_bmp,54);
    write_4b(write_bmp,40);
    if(width()>=std::numeric_limits<uint32_t>::max()) throw std::runtime_error("width is larger than .bmp requied");
    write_4b(write_bmp,static_cast<uint32_t>(width()));
    if(height()>=std::numeric_limits<uint32_t>::max()) throw std::runtime_error("height is larger than .bmp requied");
    write_4b(write_bmp,static_cast<uint32_t>(height()));
    write_2b(write_bmp,1);
    write_2b(write_bmp,24);
    write_4b(write_bmp,0);//biCompression
    write_4b(write_bmp,static_cast<uint32_t>(size));//biSizeImage
    write_4b(write_bmp,0);//biXPelsPerMeter
    write_4b(write_bmp,0);//biYPelsPerMeter
    write_4b(write_bmp,0);//biClrUsed
    write_4b(write_bmp,0);//biClrImportant

    
    for(size_t y= m_height;y-->0;)
    {
        for (size_t x = 0;x<m_width;x++)
        {
            const std::size_t idx = (y * m_width + x) * 3;

            write_bmp.put(static_cast<char>(pixel_data.at(idx + 2))); // B
            write_bmp.put(static_cast<char>(pixel_data.at(idx + 1))); // G
            write_bmp.put(static_cast<char>(pixel_data.at(idx)));     // R

        }
        
        static const char zeros[3] = {}; 
        if (padding != 0)
        {
            write_bmp.write(zeros, static_cast<std::streamsize>(padding));
        }

       
        
    }

    write_bmp.close();



    return true;

    
    
    
}
