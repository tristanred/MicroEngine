#pragma once

#include "core.h"

#include <string.h>
#include <string>

class ENGINE_CLASS ConfigFile
{
public:
    ConfigFile(const char* filepath);
    ~ConfigFile();

    std::string GetConfigValue(std::string name);

private:
    const char* LoadedFile;
};