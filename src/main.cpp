#include <ctime>
#include <iostream>
#include <random>

#include "siren/bresenham_manager.hpp"
#include "siren/model_manager.hpp"

int main(int argc, char **argv)
{
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  tga_color_t black = { 0, 0, 0 };
  tga_color_t white = { 255, 255, 255 };
  tga_color_t green = { 0, 255, 0 };
  tga_color_t red = { 0, 0, 255 };

  int width = 800;
  int height = 800;
  tga_image_t *image = tga_new(width, height);
  if (image == nullptr)
  {
    std::cerr << "Failed to allocate memory for image\n";
    return 1;
  }

  Model *model = nullptr;
  if (argc > 1)
  {
    model = new Model(argv[1]);
  }
  else
  {
    model = new Model("./obj/african_head.obj");
  }

  BresenhamManager manager(image);

  for (int i = 0; i < model->nfaces(); i++)
  {
    std::vector<int> face = model->face(i);
    if (face.size() != 3)
    {
      std::cerr << "Invalid face data\n";
      tga_free(image);
      delete model;  // Free the allocated memory
      return 1;
    }
    for (int j = 0; j < 3; j++)
    {
      Vec3f v0 = model->vert(face[j]);
      Vec3f v1 = model->vert(face[(j + 1) % 3]);
      int x0 = (v0.x + 1.) * width / 2.;
      int y0 = (v0.y + 1.) * height / 2.;
      int x1 = (v1.x + 1.) * width / 2.;
      int y1 = (v1.y + 1.) * height / 2.;
      tga_color_t randomColor = { (std::rand() % 255), (std::rand() % 255), (std::rand() % 255) };

      manager.line(x0, y0, x1, y1, image, randomColor);
    }
  }

  tga_rotate_vertical(image);
  tga_write("output.tga", image);
  tga_free(image);
  delete model;  // Free the allocated memory

  return 0;
}
