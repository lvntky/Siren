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
