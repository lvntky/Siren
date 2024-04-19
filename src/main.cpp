#include <iostream>
#include "siren/bresenham_manager.hpp"
int main() 
{
    
    tga_color_t black = {0,0,0};
    tga_color_t white = {255,255,255};

    tga_image_t *image = tga_new(1024, 1024);
    tga_set_bg(image, black);

    BresenhamManager bresenhamManager = BresenhamManager(0, 1023, 1023, 0, image, white);
    bresenhamManager.drawLine();
    bresenhamManager.setEndpoints(0, 0,1023, 0);
    bresenhamManager.setColor(white);
    bresenhamManager.drawLine();

    bresenhamManager.setEndpoints(1023, 1023,0, 1023);
    bresenhamManager.setColor(white);
    bresenhamManager.drawLine();

    tga_write("bresenham.tga", image);
    tga_free(image);
    
    return 0;
}