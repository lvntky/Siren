#include <cstdint>
#include <ctime>
#include <iostream>
#include <random>

#include "siren/bresenham_manager.hpp"
#include "siren/model_manager.hpp"

int main(int argc, char **argv)
{
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  tga_color_t grey = { 105, 105, 105 };
  uint16_t width = 800;
  uint16_t height = 800;
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
      delete model;
      return 1;
    }
    // Get vertices of the triangle
    Vec3f v0 = model->vert(face[0]);
    Vec3f v1 = model->vert(face[1]);
    Vec3f v2 = model->vert(face[2]);

    // Convert vertices to screen coordinates
    int x0 = static_cast<int>((v0.x + 1.0f) * width / 2.0f);
    int y0 = static_cast<int>((v0.y + 1.0f) * height / 2.0f);
    int x1 = static_cast<int>((v1.x + 1.0f) * width / 2.0f);
    int y1 = static_cast<int>((v1.y + 1.0f) * height / 2.0f);
    int x2 = static_cast<int>((v2.x + 1.0f) * width / 2.0f);
    int y2 = static_cast<int>((v2.y + 1.0f) * height / 2.0f);

    // Calculate normal of the triangle
    /*
    Vec3f normal = cross(v1 - v0, v2 - v0).normalize();

    // If the normal is pointing away from the camera, skip this triangle (backface culling)
    if (normal.z <= 0)
        continue;
    */

    // Fill the triangle with a random color
    tga_color_t randomColor = { static_cast<uint8_t>(std::rand() % 255),
                                static_cast<uint8_t>(std::rand() % 255),
                                static_cast<uint8_t>(std::rand() % 255) };
    manager.rasterizeTriangle(x0, y0, x1, y1, x2, y2, image, randomColor);
  }

  tga_rotate_vertical(image);
  tga_write("output.tga", image);
  tga_free(image);
  delete model;

  return 0;
}
