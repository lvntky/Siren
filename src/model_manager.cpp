#include "siren/model_manager.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "siren/bresenham_manager.hpp"

ModelManager::ModelManager(const char* filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Failed to open specified .obj file!" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line))
  {
    std::istringstream iss(line);
    std::string type;
    iss >> type;

    if (type == "v")
    {
      Vertex vertex;
      iss >> vertex.x >> vertex.y >> vertex.z;
      this->vertices.push_back(vertex);
    }
    else if (type == "f")
    {
      Face face;
      std::string v1_str, v2_str, v3_str;
      iss >> v1_str >> v2_str >> v3_str;
      // Extract vertex indices from the face line
      std::istringstream v1_ss(v1_str.substr(0, v1_str.find('/')));
      std::istringstream v2_ss(v2_str.substr(0, v2_str.find('/')));
      std::istringstream v3_ss(v3_str.substr(0, v3_str.find('/')));
      v1_ss >> face.v1;
      v2_ss >> face.v2;
      v3_ss >> face.v3;
      // OBJ indices are 1-based, so we decrement them to make them 0-based
      face.v1--;
      face.v2--;
      face.v3--;
      this->faces.push_back(face);
    }
  }
  file.close();
  std::cout << "File: " << filename << " parsed successfully!" << std::endl;
}

void line(float x0, float y0, float x1, float y1, tga_image_t* image, tga_color_t color)
{
  bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
  if (steep)
  {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  if (x0 > x1)
  {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  float dx = std::abs(x1 - x0);
  float dy = std::abs(y1 - y0);
  float error = dx / 2.0f;
  int yStep = (y0 < y1) ? 1 : -1;
  int y = static_cast<int>(y0);

  for (int x = static_cast<int>(x0); x <= static_cast<int>(x1); x++)
  {
    if (steep)
    {
      if (x >= 0 && x < image->header.height && y >= 0 && y < image->header.width)
      {
        tga_set_pixel(image, y, x, color);
      }
    }
    else
    {
      if (x >= 0 && x < image->header.width && y >= 0 && y < image->header.height)
      {
        tga_set_pixel(image, x, y, color);
      }
    }

    error -= dy;
    if (error < 0)
    {
      y += yStep;
      error += dx;
    }
  }
}

void ModelManager::render(tga_image_t* image, tga_color_t color)
{
  std::cout << "Calling the renderer" << std::endl;

  // Ensure that drawingManager is properly initialized
  BresenhamManager drawingManager(0, 0, 0, 0, image, color);

  std::cout << "Faces size: " << faces.size() << std::endl;

  // Check for out-of-bounds errors
  for (const auto& face : faces)
  {
    // Ensure that face vertex indices are within bounds
    if (face.v1 < 0 || face.v1 >= vertices.size() || face.v2 < 0 || face.v2 >= vertices.size() || face.v3 < 0 ||
        face.v3 >= vertices.size())
    {
      std::cerr << "Error: Face vertex index out of bounds!" << std::endl;
      continue;
    }

    const Vertex& v1 = vertices[face.v1];
    const Vertex& v2 = vertices[face.v2];
    const Vertex& v3 = vertices[face.v3];

    // Draw lines between vertices of the face
    line(v1.x, v1.y, v2.x, v2.y, image, color);

    line(v2.x, v2.y, v3.x, v3.y, image, color);

    line(v3.x, v3.y, v1.x, v1.y, image, color);

    // Debug: print vertex coordinates
    std::cout << "Vertex 1: (" << v1.x << ", " << v1.y << ")" << std::endl;
    std::cout << "Vertex 2: (" << v2.x << ", " << v2.y << ")" << std::endl;
    std::cout << "Vertex 3: (" << v3.x << ", " << v3.y << ")" << std::endl;
    std::cout << std::endl;
  }
}
