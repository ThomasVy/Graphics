#include "filesystem/IFilesystem.h"
#include "Filesystem.h"
std::unique_ptr<IFilesystem> GetFilesystem()
{
    return std::make_unique<Filesystem>();
}