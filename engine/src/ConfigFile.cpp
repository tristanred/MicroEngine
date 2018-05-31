#include "ConfigFile.h"

ConfigFile::ConfigFile(const char *filepath)
{
    char msg[1024];
    sprintf(msg, "ConfigFile reading %s", filepath);
    LogTrace(msg);

    doc = new pugi::xml_document();
    pugi::xml_parse_result result = doc->load_file(filepath);

    if(result)
    {
        sprintf(msg, "Config File %s opened successfully.", filepath);

        LoadedFile = filepath;
        isValid = true;
        values = new std::vector<ConfigValue*>();

        auto configNodes = doc->select_nodes("/config/data");
        auto begin = configNodes.begin();
        auto end = configNodes.end();

        while(begin != end)
        {
            pugi::xpath_node val = *begin;
            
            const char* name = val.node().attribute("name").as_string();
            const char* valueString = val.node().text().as_string();

            ConfigValue* valueStruct = new ConfigValue();
            valueStruct->Name = new char[strlen(name)+1];
            valueStruct->Value = new char[strlen(valueString)+1];

            strcpy(valueStruct->Name, name);
            strcpy(valueStruct->Value, valueString);

            values->push_back(valueStruct);

            begin++;
        }
    }
    else
    {
        sprintf(msg, "Failed to open file %s.", filepath);

        LoadedFile = NULL;
        isValid = false;
        values = NULL;
        doc = NULL;
    }
}

ConfigFile::~ConfigFile()
{
    char msg[1024];
    sprintf(msg, "Deleting config file %s", this->LoadedFile);
    LogTrace(msg);

    delete(doc);
    
    auto begin = values->begin();
    auto end = values->end();
    while(begin != end)
    {
        ConfigValue* value = *begin;
        delete[] value->Name;
        delete[] value->Value;

        delete(value);

        begin++;
    }

    delete(values);
}

std::string ConfigFile::GetConfigValue(std::string name)
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

    return "";
}

std::string ConfigFile::GetConfigValueSafe(std::string name, std::string valueIfNull)
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

    return valueIfNull;
}
