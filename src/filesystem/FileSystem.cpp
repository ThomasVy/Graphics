#include "Filesystem.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "logger/Log.h"

std::string Filesystem::ReadFile(std::string_view filePath)
{
    try {
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        file.open(filePath.data());
        std::stringstream sourceStream;
        sourceStream << file.rdbuf();
        file.close();
        return sourceStream.str();
    }
    catch (std::ifstream::failure &) {
        logger::Error("Failed to read file {}", filePath);
        throw std::runtime_error("Could not read file" );
    }
}