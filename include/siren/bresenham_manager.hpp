#ifndef BRESENHAM_MANAGER_HPP_
#define BRESENHAM_MANAGER_HPP_

#include <cmath>
#include <cstdint>

#include "../targalib/targalib.h"

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
  BresenhamManager(tga_image_t *image);
  BresenhamManager(int x0, int y0, int x1, int y1, tga_image_t *image, tga_color_t color);
  void setEndpoints(int x0, int y0, int x1, int y1);
  void setColor(tga_color_t color);
  void setImage(tga_image_t *image);
  void drawLine();
};

#endif  // BRESENHAM_MANAGER_HPP_