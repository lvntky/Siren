#include <iostream>

#include "siren/bresenham_manager.hpp"
#include "siren/model_manager.hpp"

int main(int argc, char **argv)
{
  ModelManager *model = NULL;
  if (argc > 1)
  {
    model = new ModelManager(argv[1]);
  }
  else
  {
    model = new ModelManager("./obj/african_head.obj");
  }

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

  BresenhamManager drawingManager(0, 0, 0, 0, image, black);

  for (int i = 0; i < model->getFaceNumbers(); i++)
  {
    std::vector<int> face = model->getFaceByIndex(i);
    for (int j = 0; j < 3; j++)
    {
      Vec3f v0 = model->getVerticeByIndex(face[j]);
      Vec3f v1 = model->getVerticeByIndex(face[(j + 1) % 3]);
      int x0 = (v0.x + 1.) * width / 2.;
      int y0 = (v0.y + 1.) * height / 2.;
      int x1 = (v1.x + 1.) * width / 2.;
      int y1 = (v1.y + 1.) * height / 2.;
      // line(x0, y0, x1, y1, image, white);
      std::cout << "x0: " << x0 << "y0: " << y0 << "x1: " << x1 << "y1: " << y1 << std::endl;  
      drawingManager.setEndpoints(x0, y0, x1, y1);
      drawingManager.setColor(black);
      drawingManager.drawLine();
    }
  }


  for (size_t i = 0; i < 10; i++)
  {
    drawingManager.setEndpoints(0, 0, i + 100, i + 50  );
    drawingManager.setColor(black);
    drawingManager.drawLine();
  }
  
  tga_write("output.tga", image);
  tga_free(image);

  return 0;
}
