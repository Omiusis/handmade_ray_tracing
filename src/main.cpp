#include <iostream>
#include "rt/image.h"
#include "rt/color.h"
#include "rt/vec3.h"
int main()
{
    rt::image test (800,450);

    size_t h=test.height();
    size_t w=test.width();
    for(size_t y=0;y<h;y++)
    {
        for (size_t x = 0; x <w; x++)
        {
            double r =(double)x/(double)(w-1);
            double g =(double)y/(double)(h-1);
            double b = 0.2;

            std::array<std::uint8_t,3> rgb= rt::color_to_RGB(rt::Color{r,g,b});
            test.set_pixel(x,y,rgb[0],rgb[1],rgb[2]);

        }
        
    }

    test.saved_as_bmp("src/out/");
}
