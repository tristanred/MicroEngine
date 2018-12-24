#include "FormatLoaders/FrameListLoader.h"

#include <libtech/pathutils.h>
#include <libtech/fsutils.h>
#include <string>
#include <string.h>

#include "ARenderer.h"
#include "ATexture.h"
#include "ASprite.h"

#define PUGIXML_HEADER_ONLY
#include "pugixml.hpp"

FrameListLoader::FrameListLoader(ARenderer* renderer)
{
    this->renderer = renderer;
    currentDirectory = NULL;
}

FrameListLoader::FrameListLoader(const char* framesDirectory, ARenderer* renderer)
{
    currentDirectory = framesDirectory;
    this->renderer = renderer;
}

FrameListLoader::~FrameListLoader()
{
}

void FrameListLoader::OpenDirectory(const char* framesDirectory)
{
    this->currentDirectory = framesDirectory;
}

ArrayList<ATexture*>* FrameListLoader::ExtractAsTextures()
{
    if(currentDirectory == NULL)
        return NULL;
    
    // Check if the path is a directory. If it is, we need to load many files.
    // If not, we probably point to a spritesheet that we need to decompose
    if(path_is_directory(currentDirectory))
    {
        // If we have a manifest, load the texture in the way specified by it
        // If no manifest, load all the images present
        if(this->DirectoryContainsManifest())
        {
            // Parse the XML and load the files that are needed
            
        }
        else
        {
            // Load all files
            
        }
    }
    else
    {
        // Parse the XML and interpret the spritesheet
        return this->CreateFromSpritesheet();
    }

    return NULL;
}

bool FrameListLoader::DirectoryContainsManifest()
{
    if(this->currentDirectory == NULL)
        return NULL;
    
    bool result = false;
    
    // Look for a [directoryName].xml file in the current directory.
    char* targetXmlFileName = get_file_name(currentDirectory);
    std::string xmlFileName = std::string(targetXmlFileName);
    xmlFileName.append(".xml");
    
    char* foundFile = find_subdir_file(xmlFileName.c_str(), currentDirectory);
    
    if(foundFile != NULL)
    {
        result = true;
    }
    else
    {
        result = false;
    }
    
    delete(targetXmlFileName);
    delete(foundFile);
    
    return result;
}

ArrayList<ATexture*>* FrameListLoader::CreateFromSpritesheet()
{
    ArrayList<ATexture*>* listResult = new ArrayList<ATexture*>();
    
    pugi::xml_document doc = pugi::xml_document();
    
    pugi::xml_parse_result result = doc.load_file(currentDirectory);
    
    if(result)
    {
        auto atlasNode = doc.select_node("/TextureAtlas");
        const char* spritesheetPath = atlasNode.node().attribute("imagePath").as_string();
        int sheetWidth = atlasNode.node().attribute("width").as_int();
        int sheetHeight = atlasNode.node().attribute("height").as_int();

        // SpritesheetPath is relative to the currentDirectory/File
        
        char* parentFolder = get_parent_directory_path(currentDirectory);
        std::string stringBuilder = std::string(parentFolder);
        stringBuilder.append("/");
        stringBuilder.append(spritesheetPath);

        ATexture* sheetTexture = this->renderer->CreateTexture(stringBuilder.c_str());
        
        auto frameNodes = doc.select_nodes("/TextureAtlas/sprite");
        auto begin = frameNodes.begin();
        auto end = frameNodes.end();
        
        while(begin != end)
        {
            pugi::xpath_node val = *begin;
            
            const char* filename = val.node().attribute("n").as_string();
            int tx = val.node().attribute("x").as_int();
            int ty = val.node().attribute("y").as_int();
            int tw = val.node().attribute("w").as_int();
            int th = val.node().attribute("h").as_int();
            
            ATexture* sprite = sheetTexture->GetSubTexture(tx, ty, tw, th);
            
            listResult->Add(sprite);

            begin++;
        }
        
        // delete(parentFolder); // Creates error ?

        this->renderer->DeleteTexture(sheetTexture);
    }
    else
    {
        LogTrace("Failed to open file %s.", currentDirectory);
        
        delete(listResult);
        
        return NULL;
    }
    
    return listResult;
}