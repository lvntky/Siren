#include "siren/bresenham_manager.hpp"

#include <iostream>

#include "misc/vec3f.hpp"

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

  for (float i = 0; i <= step; ++i)
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

void BresenhamManager::line(int _startX, int _startY, int _endX, int _endY, tga_image_t* _image, tga_color_t _color)
{
  bool steep = false;
  if (std::abs(_startX - _endX) < std::abs(_startY - _endY))
  {
    std::swap(_startX, _startY);
    std::swap(_endX, _endY);
    steep = true;
  }
  if (_startX > _endX)
  {
    std::swap(_startX, _endX);
    std::swap(_startY, _endY);
  }

  for (int x = _startX; x <= _endX; x++)
  {
    float t = 0.0f;
    if (_endX - _startX != 0)
    {
      t = static_cast<float>(x - _startX) / static_cast<float>(_endX - _startX);
    }
    int y = static_cast<int>(static_cast<float>(_startY) * (1.0f - t) + static_cast<float>(_endY) * t);
    if (steep)
    {
      if (y >= 0 && y < _image->header.height && x >= 0 && x < _image->header.width)
      {
        if (tga_set_pixel(_image, y, x, _color) != 0)
        {
          std::cout << "Error pixel y: " << y << " t: " << t << " y1: " << _endY << std::endl;
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
      if (x >= 0 && x < _image->header.width && y >= 0 && y < _image->header.height)
      {
        if (tga_set_pixel(_image, x, y, _color) != 0)
        {
          std::cout << "Error pixel y: " << y << " t: " << t << " y1: " << _endY << std::endl;
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

void drawHorizontalLine(int x0, int x1, int y, tga_image_t* image, tga_color_t color)
{
  for (int x = x0; x <= x1; x++)
  {
    // std::cout << "x: " << x0 << " x1: " << x1 << " y: " << y << std::endl;
    tga_set_pixel(image, x, y, color);
  }
}

void BresenhamManager::rasterizeTriangle(
    int x0,
    int y0,
    int x1,
    int y1,
    int x2,
    int y2,
    tga_image_t* image,
    tga_color_t color)
{
  // Sort vertices by y-coordinate
  if (y0 > y1)
  {
    std::swap(y0, y1);
    std::swap(x0, x1);
  }
  if (y0 > y2)
  {
    std::swap(y0, y2);
    std::swap(x0, x2);
  }
  if (y1 > y2)
  {
    std::swap(y1, y2);
    std::swap(x1, x2);
  }

  // Calculate height of the triangle
  int totalHeight = y2 - y0;

  // Fill top part of the triangle
  for (int y = y0; y <= y1; y++)
  {
    float segmentHeight = static_cast<float>(y1 - y0 + 1);
    float alpha = (segmentHeight == 1) ? 0 : static_cast<float>(y - y0) / (segmentHeight - 1);
    float beta = (totalHeight == 0) ? 0 : static_cast<float>(y - y0) / totalHeight;
    int ax = static_cast<int>(x0 + (x2 - x0) * beta);
    int bx = static_cast<int>(x0 + (x1 - x0) * alpha);
    if (ax > bx)
    {
      std::swap(ax, bx);
    }
    drawHorizontalLine(ax, bx, y, image, color);
  }

  // Fill bottom part of the triangle
  for (int y = y1 + 1; y <= y2; y++)
  {
    float segmentHeight = static_cast<float>(y2 - y1 + 1);
    float alpha = (segmentHeight == 1) ? 0 : static_cast<float>(y - y1) / (segmentHeight - 1);
    float beta = (totalHeight == 0) ? 0 : static_cast<float>(y - y0) / totalHeight;
    int ax = static_cast<int>(x1 + (x2 - x1) * alpha);
    int bx = static_cast<int>(x0 + (x2 - x0) * beta);
    if (ax > bx)
    {
      std::swap(ax, bx);
    }
    drawHorizontalLine(ax, bx, y, image, color);
  }
}