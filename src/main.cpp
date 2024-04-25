#include <cstdint>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

#include "siren/bresenham_manager.hpp"
#include "siren/model_manager.hpp"

// Function to calculate dot product of two vectors
float dot(Vec3f a, Vec3f b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

int main(int argc, char **argv)
{
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  std::vector<std::string> zVerticeVector;
  int zVectorCounter = 0;

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

  // Define light direction
  Vec3f lightDirection = { 0.0f, 0.0f, 1.0f };  // pointing towards the model

  for (int i = 0; i < model->nfaces(); i++)
  {
    std::vector<int> face = model->face(i);

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

    // z vertices of one triangle
    int z0 = static_cast<int>((v0.z + 1.0f) * height / 2.0f);
    int z1 = static_cast<int>((v1.z + 1.0f) * height / 2.0f);
    int z2 = static_cast<int>((v2.z + 1.0f) * width / 2.0f);

    //    std::cout << "z vertices of the triangle z0: " << z0 << " z1: " << z1 << " z2: " << z2 << std::endl;
    zVerticeVector.push_back(std::to_string(zVectorCounter));
    zVerticeVector.push_back(". ");
    zVerticeVector.push_back(std::to_string(z0));
    zVerticeVector.push_back(" - ");
    zVerticeVector.push_back(std::to_string(z1));
    zVerticeVector.push_back(" - ");
    zVerticeVector.push_back(std::to_string(z2));
    zVerticeVector.push_back(" end of triangle\n");

    zVectorCounter++;

    // Calculate normal of the triangle
    Vec3f normal = { 0.0f, 0.0f, 0.0f };
    Vec3f edge1 = { v1.x - v0.x, v1.y - v0.y, v1.z - v0.z };
    Vec3f edge2 = { v2.x - v0.x, v2.y - v0.y, v2.z - v0.z };
    normal.x = edge1.y * edge2.z - edge1.z * edge2.y;
    normal.y = edge1.z * edge2.x - edge1.x * edge2.z;
    normal.z = edge1.x * edge2.y - edge1.y * edge2.x;

    std::cout << "edge1: (" << edge1.x << ", " << edge1.y << ", " << edge1.z << ")" << std::endl;
    std::cout << "edge2: (" << edge2.x << ", " << edge2.y << ", " << edge2.z << ")" << std::endl;
    std::cout << "normal before normalization: (" << normal.x << ", " << normal.y << ", " << normal.z << ")" << std::endl;

    // If the normal is pointing away from the camera, skip this triangle (backface culling)
    if (normal.z <= 0)
      continue;

    // Normalize the normal
    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length == 0)
    {
      std::cerr << "Zero length normal vector encountered" << std::endl;
      continue;
    }
    normal.x /= length;
    normal.y /= length;
    normal.z /= length;

    std::cout << "normal after normalization: (" << normal.x << ", " << normal.y << ", " << normal.z << ")" << std::endl;

    // Calculate diffuse lighting
    // Calculate diffuse lighting
    float intensity = dot(normal, lightDirection);
    if (intensity < 0)
    {
      intensity = 0;  // Ensure intensity is non-negative
    }

    // Apply lighting to the color
    tga_color_t litColor = { static_cast<uint8_t>(255 * intensity),
                             static_cast<uint8_t>(255 * intensity),
                             static_cast<uint8_t>(255 * intensity) };

    std::cout << "intensity: " << intensity << std::endl;
    // Fill the triangle with the lit color
    manager.rasterizeTriangle(x0, y0, x1, y1, x2, y2, image, litColor);
  }

  tga_rotate_vertical(image);
  tga_write("output.tga", image);
  tga_free(image);


  for (auto it : zVerticeVector)
  {
    std::cout << it;
  }
  std::cerr << "# v# " << model->nverts() << " f# " << model->nfaces() << std::endl;
  delete model;

  return 0;
}
