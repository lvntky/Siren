#ifndef MODEL_PARSER_H_
#define MODEL_PARSER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "bresenham_manager.hpp" // Include the header file for BresenhamManager here

struct Vec3
{
    float x, y, z;
};

class ModelParser
{
private:
    std::vector<Vec3> vertices;
    std::vector<std::vector<int>> faces;

public:
    ModelParser(const std::string &filename);
    void printModelInfo();
    void render(BresenhamManager &renderer, tga_color_t color);
};

#endif // MODEL_PARSER_H_
