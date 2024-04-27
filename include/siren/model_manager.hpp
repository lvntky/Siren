#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

#include "misc/vec3f.hpp"

class Model
{
 private:
  std::vector<Vec3f> verts_;
  std::vector<std::vector<int>> faces_;
  std::vector<Vec3f> textureCoordinates;  // actually, vec2f is enough to calculate, but im too lasy to implement rn
  std::vector<std::vector<int>> textureFaces;

 public:
  Model(const char *filename);
  ~Model();
  int nverts();
  int nfaces();
  Vec3f vert(int i);
  std::vector<int> face(int idx);
  Vec3f getTextureCoordinates(int i);  // the z coordinate is always null. eg. {12, 5, NULL}
  std::vector<int> getTextureFace(int idx);
};

#endif  //__MODEL_H__
