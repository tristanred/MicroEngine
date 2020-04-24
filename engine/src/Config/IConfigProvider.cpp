#include <Config/IConfigProvider.h>

IConfigProvider::IConfigProvider()
{
    this->parent = NULL;
}

IConfigProvider::~IConfigProvider()
{
}

void IConfigProvider::SetParent(IConfigProvider* parent)
{
    this->parent = parent;
}

void IConfigProvider::AttachProvider(IConfigProvider* newProvider)
{
    if(this->parent == NULL)
    {
        this->parent = newProvider;
    }
    else
    {
        this->parent->AttachProvider(newProvider);
    }
}

std::string IConfigProvider::QueryParent(std::string name)
{
    if(this->parent != NULL)
    {
        return this->parent->GetConfigValue(name);
    }

    return "";
}

std::string IConfigProvider::QueryParentSafe(std::string name, std::string valueIfNull)
{
    if(this->parent != NULL)
    {
        return this->parent->GetConfigValueSafe(name, valueIfNull);
    }

    return valueIfNull;
}
