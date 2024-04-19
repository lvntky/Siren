#ifndef MODEL_PARSER_H_
#define MODEL_PARSER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct Vec3
{
    float x, y, z;
};

struct FaceVertex
{
    int vertexIndex;
    int normalIndex;
};

class ModelParser
{
private:
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<FaceVertex> faces;
public:
    ModelParser(const std::string& filename);
    void printModelInfo();
    ~ModelParser();
};

#endif //MODEL_PARSER_H_