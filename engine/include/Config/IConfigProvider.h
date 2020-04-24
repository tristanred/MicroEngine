#pragma once

#include <string>

#include "core.h"

struct ENGINE_CLASS ConfigValue
{
    char* Name;
    char* Value;
};

class ENGINE_CLASS IConfigProvider
{
public:
    IConfigProvider();
    virtual ~IConfigProvider();

    virtual std::string GetConfigValue(std::string name) = 0;

    virtual std::string GetConfigValueSafe(std::string name,
                                           std::string valueIfNull) = 0;

    virtual void SetParent(IConfigProvider* parent);

    virtual void AttachProvider(IConfigProvider* newProvider);

protected:
    IConfigProvider* parent;

    virtual std::string QueryParent(std::string name);
    virtual std::string QueryParentSafe(std::string name,
                                        std::string valueIfNull);
};