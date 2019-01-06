#include "FormatLoaders/TPXmlReader.h"

#include "pugixml.hpp"
#include <string>
#include <string.h>

TPXmlReader::TPXmlReader(const char* path)
{
    this->loadedPath = path;
}

TPXmlReader::~TPXmlReader()
{
}

ArrayList<TPXmlEntry*>* TPXmlReader::ReadEntries(TPXmlHeader* outHeaderInfo)
{
    if(loadedPath == NULL)
        return NULL;
    
    pugi::xml_document doc = pugi::xml_document();
    
    pugi::xml_parse_result result = doc.load_file(loadedPath);
    
    if(result)
    {
        ArrayList<TPXmlEntry*>* listResult = new ArrayList<TPXmlEntry*>();
        
        // Header information
        auto atlasNode = doc.select_node("/TextureAtlas");
        const char* spritesheetPath = atlasNode.node().attribute("imagePath").as_string();
        int sheetWidth = atlasNode.node().attribute("width").as_int();
        int sheetHeight = atlasNode.node().attribute("height").as_int();

        if (outHeaderInfo != NULL)
        {
            outHeaderInfo->imagePath = new char[strlen(spritesheetPath) + 1];
            strcpy(outHeaderInfo->imagePath, spritesheetPath);

            outHeaderInfo->width = sheetWidth;
            outHeaderInfo->height = sheetHeight;
        }
        
        auto frameNodes = doc.select_nodes("/TextureAtlas/sprite");
        auto begin = frameNodes.begin();
        auto end = frameNodes.end();
        
        while(begin != end)
        {
            TPXmlEntry* tpEntry = new TPXmlEntry();
            
            pugi::xpath_node val = *begin;
            
            // Copy the required information
            const char* filename = val.node().attribute("n").as_string();
            tpEntry->name = new char[strlen(filename) + 1];
            strcpy(tpEntry->name, filename);
            
            tpEntry->x = val.node().attribute("x").as_int();
            tpEntry->y = val.node().attribute("y").as_int();
            tpEntry->w = val.node().attribute("w").as_int();
            tpEntry->h = val.node().attribute("h").as_int();
            
            // Copy optional information
            tpEntry->oX = val.node().attribute("oX").as_int(0);
            tpEntry->oY = val.node().attribute("oY").as_int(0);
            tpEntry->oW = val.node().attribute("oW").as_int(0);
            tpEntry->oH = val.node().attribute("oH").as_int(0);
            
            // Set the rotation value to 'r' or 0 if not present
            if(strcmp(val.node().attribute("r").as_string(), "r") == 0)
            {
                tpEntry->r = 'r';
            }
            else
            {
                tpEntry->r = 0;
            }
               
            listResult->Add(tpEntry);

            begin++;
        }

        return listResult;
    }

    return NULL;
}

ArrayList<char*>* TPXmlReader::GetFileNames()
{
    if(loadedPath == NULL)
        return NULL;
    
    pugi::xml_document doc = pugi::xml_document();
    
    pugi::xml_parse_result result = doc.load_file(loadedPath);
    
    if(result)
    {
        ArrayList<char*>* listResult = new ArrayList<char*>();
        
        auto frameNodes = doc.select_nodes("/TextureAtlas/sprite");
        auto begin = frameNodes.begin();
        auto end = frameNodes.end();
        
        while(begin != end)
        {
            pugi::xpath_node val = *begin;
            
            const char* filename = val.node().attribute("n").as_string();
            char* listName = new char[strlen(filename) + 1];
            strcpy(listName, filename);

            listResult->Add(listName);

            begin++;
        }

        return listResult;
    }

    return NULL;
}

TPXmlEntry::TPXmlEntry()
{
    this->name = NULL;
}

TPXmlEntry::~TPXmlEntry()
{
    if (this->name != NULL)
    {
        delete(this->name);
    }
}

TPXmlHeader::TPXmlHeader()
{
    this->imagePath = NULL;
}

TPXmlHeader::~TPXmlHeader()
{
    if (this->imagePath != NULL)
    {
        delete(this->imagePath);
    }
}
