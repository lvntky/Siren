#include <iostream>

#include "siren/bresenham_manager.hpp"
#include "siren/model_manager.hpp"

int main()
{
  tga_color_t black = { 0, 0, 0 };
  tga_color_t white = { 255, 255, 255 };

  tga_image_t *image = tga_new(1024, 1024);
  if (!image)
  {
    std::cerr << "Failed to create image" << std::endl;
    return 1;
  }
  tga_set_bg(image, white);

  tga_write("output.tga", image);
  tga_free(image);

  return 0;
}
