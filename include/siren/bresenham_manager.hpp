#ifndef BRESENHAM_MANAGER_HPP_
#define BRESENHAM_MANAGER_HPP_

#include <cstdint>
#include <cmath>
#include "../targalib/targalib.h"
#include "common.hpp"

class BresenhamManager
{
private:
    int x0;
    int x1;
    int y0;
    int y1;
    tga_image_t *image;
    tga_color_t color;
public:
    BresenhamManager();
    BresenhamManager(int x0, int y0, int x1, int y1, tga_image_t *image, tga_color_t color);
    void setEndpoints(int x0, int y0, int x1, int y1);
    void setColor(tga_color_t color);
    void drawLine();
};

#endif //BRESENHAM_MANAGER_HPP_