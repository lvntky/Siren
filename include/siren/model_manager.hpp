#ifndef MODEL_MANAGER_H_
#define MODEL_MANAGER_H_

#include <string>
#include <vector>

#include "targalib/targalib.h"

struct Vertex
{
  float x, y, z;
};

struct Face
{
  int v1, v2, v3;
};

class ModelManager
{
 private:
  std::vector<Vertex> vertices;
  std::vector<Face> faces;

 public:
  ModelManager(const char* filename);
  void render(tga_image_t* image, tga_color_t color);
};

#endif  // MODEL_MANAGER_H_
