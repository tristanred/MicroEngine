#pragma once

#include <string.h>

#include <string>
#include <vector>

#include "IConfigProvider.h"
#include "core.h"
#include "pugixml.hpp"

class ENGINE_CLASS FileConfigProvider : public IConfigProvider
{
public:
    FileConfigProvider(const char* filepath);
    ~FileConfigProvider();

    std::string GetConfigValue(std::string name);
    std::string GetConfigValueSafe(std::string name, std::string valueIfNull);

private:
    const char* LoadedFile;
    pugi::xml_document* doc;
    std::vector<ConfigValue*>* values;

    bool isValid;
};