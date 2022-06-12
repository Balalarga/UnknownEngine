#pragma once
#include <string>

class FileSystem
{
public:
    FileSystem() = delete;

    static std::string ReadFile(const std::string& filepath);
    
};
