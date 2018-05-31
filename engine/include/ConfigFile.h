#pragma once

#include "core.h"

#include <vector>
#include <string.h>
#include <string>
#include "pugixml.hpp"

struct ENGINE_CLASS ConfigValue
{
    char* Name;
    char* Value;
};

class ENGINE_CLASS ConfigFile
{
public:
    ConfigFile(const char* filepath);
    ~ConfigFile();

    std::string GetConfigValue(std::string name);
    std::string GetConfigValueSafe(std::string name, std::string valueIfNull);

private:
    const char* LoadedFile;
    pugi::xml_document* doc;
    std::vector<ConfigValue*>* values;

    bool isValid;
};