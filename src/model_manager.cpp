#include "siren/model_manager.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/*
ModelManager(const std::string& source);
    int getVerticeNumbers();
    int getFaceNumbers();
    Vec3f getVerticeByIndex(int i);
    std::vector<int> getFaceByIndex(int i);
*/

ModelManager::ModelManager(const char *filename)
{
  std::ifstream in;
  in.open(filename, std::ifstream::in);

  if (!in.is_open())
  {
    std::cerr << "Failed to open given obj file: " << filename << std::endl;
    return;
  }

  std::string line;
  while (!in.eof())
  {
    std::getline(in, line);
    std::istringstream iss(line.c_str());
    char trash;

    if (!line.compare(0, 2, "v "))
    {
      iss >> trash;
      Vec3f v;
      for (int i = 0; i < 3; i++)
        iss >> v.raw[i];
      this->vertices.push_back(v);
    }
    else if (!line.compare(0, 2, "f "))
    {
      std::vector<int> f;
      int itrash, idx;
      iss >> trash;
      while (iss >> idx >> trash >> itrash >> trash >> itrash)
      {
        idx--;  // in wavefront obj all indices start at 1, not zero
        f.push_back(idx);
      }
      this->faces.push_back(f);
    }
  }
  std::cerr << "# v# " << this->vertices.size() << " f# " << this->faces.size() << std::endl;
}

int ModelManager::getVerticeNumbers()
{
  return (int)vertices.size();
}
int ModelManager::getFaceNumbers()
{
  return (int)faces.size();
}
Vec3f ModelManager::getVerticeByIndex(int i)
{
  return this->vertices.at(i);
}
std::vector<int> ModelManager::getFaceByIndex(int i)
{
  return faces[i];
}