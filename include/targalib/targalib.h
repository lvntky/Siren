// targalib.h - v0.1.0 - Targa image manipulation library - public domain
// Levent Kaya, Apr 2024
//
// Designed to be compact
// Easy to use
// Utilized throug several Computer Graphics projects
//
// Documentation
// TAR Spesification document : https://www.gamers.org/dEngine/quake3/TGA.txt
//
// Version History
// 17-04-2024   v0.1.0  Initial Release
//
// License
// See the end of the file

#ifndef __TARGALIB_H__
#define __TARGALIB_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGALIB_ERROR "[ERROR] targalib.h  |"
#define RETURN_FAIL    1
#define RETURN_SUCCESS 0

typedef struct tga_header
{
  uint8_t id_length;
  uint8_t color_map_type;
  uint8_t image_type;
  uint16_t color_map_origin;
  uint16_t color_map_length;
  uint8_t color_map_depth;
  uint16_t x_origin;
  uint16_t y_origin;
  uint16_t width;
  uint16_t height;
  uint8_t bits_per_pixel;
  uint8_t image_descriptor;
} tga_header_t;

typedef struct tga_color
{
  uint8_t b;
  uint8_t g;
  uint8_t r;
} tga_color_t;

typedef struct tga_image
{
  tga_header_t header;
  tga_color_t *image_data;
} tga_image_t;

#ifdef __cplusplus
extern "C"
{
#endif

  tga_image_t *tga_new(uint16_t width, uint16_t height);
  void tga_free(tga_image_t *image);
  int tga_read(const char *filename, tga_image_t *image);
  int tga_write(const char *filename, const tga_image_t *image);
  void tga_set_pixel(const tga_image_t *image, int x, int y, tga_color_t color);
  void tga_set_bg(const tga_image_t *image, tga_color_t color);
  void tga_flip_horizontally();
  void tga_flip_vertically();
  int tga_resize_image(tga_image_t *image, int new_width, int new_height);
  void tga_dump_headers(const tga_image_t *image, const char *output_file);

#ifdef __cplusplus
}
#endif

#endif  //__TARGALIB_H__

//#ifdef TARGALIB_IMPLEMENTATION