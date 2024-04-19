#include "siren/bresenham_manager.hpp"

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