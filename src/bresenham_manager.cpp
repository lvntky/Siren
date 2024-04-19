#include "siren/bresenham_manager.hpp"

BresenhamManager::BresenhamManager(tga_image_t *_image) {
    this->image = _image;
}

BresenhamManager::BresenhamManager(int _x0, int _y0, int _x1, int _y1, tga_image_t *_image, tga_color_t _color) {
    this->x0 = _x0;
    this->y0 = _y0;
    this->x1 = _x1;
    this->y1 = _y1;
    this->image = _image;
    this->color = _color;
}

void BresenhamManager::setEndpoints(int _x0, int _y0, int _x1, int _y1) {
    this->x0 = _x0;
    this->y0 = _y0;
    this->x1 = _x1;
    this->y1 = _y1;
}

void BresenhamManager::setColor(tga_color_t _color) {
    this->color = _color;
}

void BresenhamManager::drawLine() {
   int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        tga_set_pixel(image, x0, y0, color);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void BresenhamManager::setImage(tga_image_t *_image) {
    this->image = _image;
}