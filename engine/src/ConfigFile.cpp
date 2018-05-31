#include "ConfigFile.h"

ConfigFile::ConfigFile(const char *filepath)
{
    doc = new pugi::xml_document();
    pugi::xml_parse_result result = doc->load_file(filepath);

    if(result)
    {
        isValid = true;
    }
    else
    {
        isValid = false;
    }
}

ConfigFile::~ConfigFile()
{
    delete(doc);
}

std::string ConfigFile::GetConfigValue(std::string name)
{
    char xpath[1024];
    sprintf(xpath, "/config/data[@name='%s']", name.c_str());

    auto x = doc->select_node(xpath);

    return x.node().text().as_string();
}
