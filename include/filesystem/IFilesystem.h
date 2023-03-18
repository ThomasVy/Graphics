#pragma once
#include <string>
#include <memory>

class IFilesystem
{
public:
    virtual ~IFilesystem() = default;

    virtual std::string ReadFile(std::string_view filePath) = 0;
};

std::unique_ptr<IFilesystem> GetFilesystem();