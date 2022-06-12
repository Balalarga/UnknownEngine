#include "FileSystem.h"
#include <fstream>
#include <sstream>


std::string FileSystem::ReadFile(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file)
        return "";

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    return stream.str();
}
