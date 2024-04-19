#include <iostream>

#include "siren/bresenham_manager.hpp"
#include "siren/model_manager.hpp"

int main(int argc, char **argv)
{
  tga_color_t black = { 0, 0, 0 };
  tga_color_t white = { 255, 255, 255 };

  int width = 800;
  int height = 800;
  tga_image_t *image = tga_new(width, height);
  if (!image)
  {
    std::cerr << "Failed to create image" << std::endl;
    return 1;
  }
  tga_set_bg(image, white);

  ModelManager *model = NULL;
  model = new ModelManager("./obj/african_head.obj");

  model->render(image, black);

  tga_write("output.tga", image);
  tga_free(image);

  return 0;
}
