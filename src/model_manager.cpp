#include "siren/model_manager.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Model::Model(const char *filename) : verts_(), faces_(), textureCoordinates(), textureFaces()
{
  std::ifstream in;
  in.open(filename, std::ifstream::in);
  if (in.fail())
    return;
  std::string line;
  while (std::getline(in, line))
  {
    std::istringstream iss(line);
    char trash;
    if (!line.compare(0, 2, "v "))
    {
      iss >> trash;
      Vec3f v;
      for (int i = 0; i < 3; i++)
        iss >> v[i];  // Use operator[] to set components
      verts_.push_back(v);
    }
    else if (!line.compare(0, 3, "vt "))  // Texture coordinate line
    {
      iss >> trash >> trash;  // Discard "vt"
      Vec3f vt;
      for (int i = 0; i < 3; i++)
        iss >> vt[i];
      textureCoordinates.push_back(vt);
    }
    else if (!line.compare(0, 2, "f "))
    {
      std::vector<int> f;
      std::vector<int> tf;  // Texture face
      int itrash, idx;
      iss >> trash;
      while (iss >> idx >> trash >> itrash >> trash >> itrash)
      {
        idx--;  // in wavefront obj all indices start at 1, not zero
        f.push_back(idx);
        tf.push_back(itrash - 1);  // Texture indices start from 1 in OBJ format
      }
      faces_.push_back(f);
      textureFaces.push_back(tf);
    }
  }
  std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;
}

Model::~Model()
{
}

int Model::nverts()
{
  return static_cast<int>(verts_.size());
}

int Model::nfaces()
{
  return static_cast<int>(faces_.size());
}

Vec3f Model::vert(int i)
{
  return verts_[i];
}

std::vector<int> Model::face(int idx)
{
  return faces_[idx];
}

Vec3f Model::getTextureCoordinates(int i)
{
  return textureCoordinates[i];
}

std::vector<int> Model::getTextureFace(int idx)
{
  return textureFaces[idx];
}
