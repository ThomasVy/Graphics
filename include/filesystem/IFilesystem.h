#pragma once
#include <string>
#include <memory>
#include <optional>

class IFilesystem
{
public:
    virtual ~IFilesystem() = default;

    virtual std::optional<std::string> ReadFile(std::string_view filePath) = 0;
};

std::unique_ptr<IFilesystem> GetFilesystem();