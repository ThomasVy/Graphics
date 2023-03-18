#pragma once
#include <string>
#include "filesystem/IFilesystem.h"

class Filesystem : public IFilesystem
{
public:
    std::string ReadFile(std::string_view filePath);
};