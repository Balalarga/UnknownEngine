#include "FileSystem.h"
#include <fstream>
#include <sstream>

const std::string FileSystem::sResourcesPath = RESOURCES_FOLDER_PATH;

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

std::string FileSystem::ReadResource(const std::string& filepath)
{
    return ReadFile(sResourcesPath + "/" + filepath);
}
