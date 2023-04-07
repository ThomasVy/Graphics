#pragma once
#include <string>
#include "filesystem/IFilesystem.h"

class Filesystem : public IFilesystem
{
public:
    std::optional<std::string> ReadFile(std::string_view filePath) override;
};