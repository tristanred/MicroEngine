#include "Config/InMemoryProvider.h"

InMemoryProvider::InMemoryProvider()
{
    this->values = new std::vector<ConfigValue*>();
}

InMemoryProvider::~InMemoryProvider()
{
    auto begin = values->begin();
    auto end = values->end();
    while(begin != end)
    {
        delete(*begin);

        begin++;
    }
}

void InMemoryProvider::AddValue(std::string name, std::string value)
{
    ConfigValue* newVal = new ConfigValue();
    newVal->Name = new char[name.size()];
    newVal->Value = new char[value.size()];

    strcpy(newVal->Name, name.c_str());
    strcpy(newVal->Value, value.c_str());

    this->values->push_back(newVal);
}

std::string InMemoryProvider::GetConfigValue(std::string name)
{
    auto begin = values->begin();
    auto end = values->end();
    while(begin != end)
    {
        ConfigValue* value = *begin;

        if(value->Name == name)
        {
            return value->Value;
        }

        begin++;
    }

    return this->QueryParent(name);
}

std::string InMemoryProvider::GetConfigValueSafe(std::string name,
                                                 std::string valueIfNull)
{
    auto begin = values->begin();
    auto end = values->end();
    while(begin != end)
    {
        ConfigValue* value = *begin;

        if(value->Name == name)
        {
            return value->Value;
        }

        begin++;
    }

    return this->QueryParentSafe(name, valueIfNull);
}
