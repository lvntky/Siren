#include "siren/bresenham_manager.hpp"

#include <iostream>

BresenhamManager::BresenhamManager(tga_image_t* _image)
{
  this->image = _image;
}

BresenhamManager::BresenhamManager(float _x0, float _y0, float _x1, float _y1, tga_image_t* _image, tga_color_t _color)
{
  this->x0 = _x0;
  this->y0 = _y0;
  this->x1 = _x1;
  this->y1 = _y1;
  this->image = _image;
  this->color = _color;
}

void BresenhamManager::setEndpoints(float _x0, float _y0, float _x1, float _y1)
{
  this->x0 = _x0;
  this->y0 = _y0;
  this->x1 = _x1;
  this->y1 = _y1;
}

void BresenhamManager::setColor(tga_color_t _color)
{
  this->color = _color;
}

void BresenhamManager::drawLine()
{
  float dx = x1 - x0;
  float dy = y1 - y0;
  float step = std::max(std::abs(dx), std::abs(dy));  // Determine the number of steps needed
  float xIncrement = dx / step;
  float yIncrement = dy / step;

  float x = x0;
  float y = y0;

  for (int i = 0; i <= step; ++i)
  {
    int intX = static_cast<int>(x + 0.5f);  // Round to nearest integer
    int intY = static_cast<int>(y + 0.5f);  // Round to nearest integer
    tga_set_pixel(image, intX, intY, color);
    x += xIncrement;
    y += yIncrement;
  }
}

void BresenhamManager::setImage(tga_image_t* _image)
{
  this->image = _image;
}

void BresenhamManager::line(int x0, int y0, int x1, int y1, tga_image_t* image, tga_color_t color)
{
  bool steep = false;
  if (std::abs(x0 - x1) < std::abs(y0 - y1))
  {
    std::swap(x0, y0);
    std::swap(x1, y1);
    steep = true;
  }
  if (x0 > x1)
  {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  for (int x = x0; x <= x1; x++)
  {
    float t = 0.0f;
    if (x1 - x0 != 0)
    {
      t = (x - x0) / static_cast<float>(x1 - x0);
    }
    int y = y0 * (1. - t) + y1 * t;
    if (steep)
    {
      if (y >= 0 && y < image->header.height && x >= 0 && x < image->header.width)
      {
        if (tga_set_pixel(image, y, x, color) != 0)
        {
          std::cout << "Error pixel y: " << y << " t: " << t << " y1: " << y1 << std::endl;
        }
      }
      else
      {
        std::cout << "Out of bounds: "
                  << " y: " << y << " x: " << x << std::endl;
      }
    }
    else
    {
      if (x >= 0 && x < image->header.width && y >= 0 && y < image->header.height)
      {
        if (tga_set_pixel(image, x, y, color) != 0)
        {
          std::cout << "Error pixel y: " << y << " t: " << t << " y1: " << y1 << std::endl;
        }
      }
      else
      {
        std::cout << "Out of bounds: "
                  << " x: " << x << " y: " << y << std::endl;
      }
    }
  }
}