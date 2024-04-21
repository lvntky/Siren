#include <iostream>

#include "siren/bresenham_manager.hpp"
#include "siren/model_manager.hpp"

int main(int argc, char **argv)
{
  tga_color_t black = { 0, 0, 0 };
  tga_color_t white = { 255, 255, 255 };
  tga_color_t green = { 0, 255, 0 };
  tga_color_t red = { 0, 0, 255 };

  int width = 800;
  int height = 800;
  tga_image_t *image = tga_new(width, height);

  Model *model = NULL;
  if (argc > 1)
  {
    model = new Model(argv[1]);
  } else {
    model = new Model("./obj/african_head.obj");
  }
  
  BresenhamManager manager = NULL;
  manager.setImage(image);

  for (int i = 0; i < model->nfaces(); i++)
  {
    std::vector<int> face = model->face(i);
    for (int j = 0; j < 3; j++)
    {
      Vec3f v0 = model->vert(face[j]);
      Vec3f v1 = model->vert(face[(j + 1) % 3]);
      int x0 = (v0.x + 1.) * width / 2.;
      int y0 = (v0.y + 1.) * height / 2.;
      int x1 = (v1.x + 1.) * width / 2.;
      int y1 = (v1.y + 1.) * height / 2.;
      tga_color_t color = white;
      switch (j)
      {
        case 1: color = red; break;
        case 2: color = green; break;
        case 3: color = white; break;
        default: break;
      }

      manager.line(x0, y0, x1, y1, image, color);
    }
  }

  tga_rotate_vertical(image);
  tga_write("output.tga", image);
  tga_free(image);

  return 0;
}
