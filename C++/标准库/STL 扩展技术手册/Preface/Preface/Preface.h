#pragma once

#include <string>

class DIR
{
};

struct dirent
{
    const char* d_name;
};

inline DIR* opendir([[maybe_unused]] const std::string& directory)
{
    return nullptr;
}

inline dirent* readdir([[maybe_unused]] DIR* dir)
{
    return nullptr;
}

inline void closedir([[maybe_unused]] DIR* dir)
{
}

class dynamic_library
{
public:
    explicit dynamic_library([[maybe_unused]] const char* pathName)
    {
    }
};