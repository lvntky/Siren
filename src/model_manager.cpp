#include "siren/model_manager.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/*
ModelManager(const std::string& source);
    int getVerticeNumbers();
    int getFaceNumbers();
    Vec3f getVerticeByIndex(int i);
    std::vector<int> getFaceByIndex(int i);
*/

ModelManager::ModelManager(const char *filename)
{
    std::ifstream in;
}