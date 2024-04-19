#ifndef MODEL_MANAGER_H_
#define MODEL_MANAGER_H_

#include <string>
#include <vector>

#include "bresenham_manager.hpp"
#include "misc/vec3f.hpp"

class ModelManager
{
 private:
  std::vector<Vec3f> vertices;
  std::vector<std::vector<int>> faces;

 public:
  ModelManager(const char *source);
  int getVerticeNumbers();
  int getFaceNumbers();
  Vec3f getVerticeByIndex(int i);
  std::vector<int> getFaceByIndex(int i);
};

#endif  // MODEL_MANAGER_H_
