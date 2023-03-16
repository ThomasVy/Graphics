#pragma once
#include "fmt/core.h"
#include <string_view>

template <typename ...ARGS> 
auto myFormat(std::string_view fmt, ARGS&&... args)
{
    return fmt::format(fmt::runtime(fmt), std::forward<ARGS>(args)...);
}