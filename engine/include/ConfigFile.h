#pragma once

#include "core.h"

#include <vector>
#include <string.h>
#include <string>
#include "pugixml.hpp"

/**
 * \brief Individual config value.
 *
 * Used to index the value of each configuration value to a searchable name.
 */
struct ENGINE_CLASS ConfigValue
{
    char* Name;
    char* Value;
};

/**
 * \brief Configuration file to read values from by name.
 *
 * Currently does not support saving data. The config must be in a specific
 * XML format.
 */
class ENGINE_CLASS ConfigFile
{
public:
    ConfigFile(const char* filepath);
    ~ConfigFile();

    /**
     * \brief Get a config value from the file.
     *
     * \param name - Name of the config value.
     *
     * \return std::string - Data of the config value.
     */
    std::string GetConfigValue(std::string name);

    /**
     * \brief Get a config value from the file. Giving a value that will
     * returned if the search finds nothing.
     *
     * \param name - Name of the config value.
     * \param valueIfNull - Value returned if the config does not contain the
     * sought value.
     *
     * \return std::string - Data of the config value.
     */
    std::string GetConfigValueSafe(std::string name, std::string valueIfNull);

private:
    const char* LoadedFile;
    pugi::xml_document* doc;
    std::vector<ConfigValue*>* values;

    bool isValid;
};