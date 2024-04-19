#include "siren/model_parser.hpp"

ModelParser::ModelParser(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open obj file:" << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v")
        {
            Vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            this->vertices.push_back(vertex);
        }
        else if (prefix == "f") // Fix: Change "y" to "f" to parse face data
        {
            std::vector<int> faceIndices;
            int index;
            while (iss >> index)
            {
                faceIndices.push_back(index - 1);
            }
            this->faces.push_back(faceIndices);
        }
    }
    file.close();
    std::cout << "obj:<" << filename << "> loaded successfully!" << std::endl;
}

void ModelParser::render(BresenhamManager &manager, tga_color_t color)
{
    for (const auto &face : faces)
    {
        for (size_t i = 0; i < face.size(); ++i)
        {
            const Vec3 &v0 = vertices[face[i]];
            const Vec3 &v1 = vertices[face[(i + 1) % face.size()]]; // Connect last vertex to first
            manager.setEndpoints(v0.x, v0.y, v1.x, v1.y);
            std::cout << "Endpoints" << std::endl
                      << v0.x << v0.y << v1.x << v1.y << std::endl;
            manager.setColor(color);
            manager.drawLine();
        }
    }
}
