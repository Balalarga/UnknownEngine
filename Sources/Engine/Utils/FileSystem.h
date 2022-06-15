#pragma once
#include <string>

class FileSystem
{
public:
    FileSystem() = delete;

    static std::string ReadFile(const std::string& filepath);
    static std::string ReadResource(const std::string& filepath);

    static const std::string sResourcesPath;
    
};
