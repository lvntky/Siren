#include "siren/bresenham_manager.hpp"
#define TARGALIB_IMPLEMENTATION

BresenhamManager::BresenhamManager(int x0, int y0, int x1, int y1, tga_image_t *image, tga_color_t color) {
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
    this->image = image;
    this->color = color;
}

void BresenhamManager::setEndpoints(int x0, int y0, int x1, int y1) {
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
}

void BresenhamManager::setColor(tga_color_t color) {
    this->color = color;
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