#pragma once

#include "core.h"

#include <string.h>
#include <string>
#include "pugixml.hpp"

class ENGINE_CLASS ConfigFile
{
public:
    ConfigFile(const char* filepath);
    ~ConfigFile();

    std::string GetConfigValue(std::string name);

private:
    const char* LoadedFile;
    pugi::xml_document* doc;

    bool isValid;
};