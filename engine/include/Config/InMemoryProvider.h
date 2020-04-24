#pragma once

#include "IConfigProvider.h"

#include "core.h"
#include <vector>

class ENGINE_CLASS InMemoryProvider : public IConfigProvider
{
public:
    InMemoryProvider();
    ~InMemoryProvider();

    void AddValue(std::string name, std::string value);

    std::string GetConfigValue(std::string name);
    std::string GetConfigValueSafe(std::string name, std::string valueIfNull);

private:
    std::vector<ConfigValue*>* values;
};