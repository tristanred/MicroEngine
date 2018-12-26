#include "FormatLoaders/FrameListLoader.h"

#include <libtech/pathutils.h>
#include <libtech/fsutils.h>
#include <string>
#include <string.h>

#include "ARenderer.h"
#include "ATexture.h"
#include "ASprite.h"
#include "FormatLoaders/TPXmlReader.h"

#include "pugixml.hpp"

FrameListLoader::FrameListLoader(ARenderer* renderer)
{
    this->renderer = renderer;
    currentPath = NULL;
}

FrameListLoader::FrameListLoader(const char* framesDirectory, ARenderer* renderer)
{
    currentPath = framesDirectory;
    this->renderer = renderer;
}

FrameListLoader::~FrameListLoader()
{
}

void FrameListLoader::Open(const char* framesDirectory)
{
    this->currentPath = framesDirectory;
}

char** FrameListLoader::ExtractAsArray(int* framesAmount)
{
    if(path_is_directory(currentPath))
    {
        ArrayList<char*>* filesList = new ArrayList<char*>();
        get_directory_files(currentPath, false, filesList);

        char** ret = filesList->GetListData();

        *framesAmount = (int)filesList->Count();

        delete(filesList);

        return ret;
    }
    else
    {
        
    }

    return NULL;
}

ArrayList<char*>* FrameListLoader::ExtractAsList()
{
    ArrayList<char*>* filesList = new ArrayList<char*>();
    get_directory_files(currentPath, false, filesList);

    return filesList;
}

ArrayList<ATexture*>* FrameListLoader::ExtractAsTextures()
{
    if(currentPath == NULL)
        return NULL;
    
    // Check if the path is a directory. If it is, we need to load many files.
    // If not, we probably point to a spritesheet that we need to decompose
    if(path_is_directory(currentPath))
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


SpriteAnimation* FrameListLoader::ExtractAsAnimation(const char* name)
{
    SpriteAnimation* anim = new SpriteAnimation();
    anim->AnimationName = new char[strlen(name)+1];
    strcpy(anim->AnimationName, name);

    anim->currentFrameIndex = 0;
    anim->Textures = this->ExtractAsTextures();

    return anim;
}

bool FrameListLoader::DirectoryContainsManifest()
{
    if(this->currentPath == NULL)
        return NULL;
    
    bool result = false;
    
    // Look for a [directoryName].xml file in the current directory.
    char* targetXmlFileName = get_file_name(currentPath);
    std::string xmlFileName = std::string(targetXmlFileName);
    xmlFileName.append(".xml");
    
    char* foundFile = find_subdir_file(xmlFileName.c_str(), currentPath);
    
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
    TPXmlReader rdr = TPXmlReader(currentPath);
    TPXmlHeader tpHeader;

    ArrayList<TPXmlEntry*>* entries = rdr.ReadEntries(&tpHeader);

    if (entries == NULL)
    {
        // No entries found.
        TPXmlReader rdr = TPXmlReader(currentPath);
        LogError("No TP entries found in file %s", currentPath);

        return NULL;
    }

    ArrayList<ATexture*>* listResult = new ArrayList<ATexture*>();

    char* parentFolder = get_parent_directory_path(currentPath);
    std::string stringBuilder = std::string(parentFolder);
    stringBuilder.append("/");
    stringBuilder.append(tpHeader.imagePath);

    ATexture* sheetTexture = this->renderer->CreateTexture(stringBuilder.c_str());

    auto begin = entries->GetContainer()->begin();
    auto end = entries->GetContainer()->end();

    while (begin != end)
    {
        TPXmlEntry* entry = *begin;

        ATexture* sprite = sheetTexture->GetSubTexture(entry->x, entry->y, entry->w, entry->h);

        listResult->Add(sprite);

        begin++;
    }
    
    this->renderer->DeleteTexture(sheetTexture);
    
    return listResult;
}