#pragma once

struct SpriteAnimation;
class ARenderer;
class ATexture;

#include "core.h"
#include <libtech/arraylist.h>

class ENGINE_CLASS FrameListLoader
{
public:
    FrameListLoader(ARenderer* renderer = NULL);
    FrameListLoader(const char* framesDirectory, ARenderer* renderer = NULL);
    ~FrameListLoader();
    
    void OpenDirectory(const char* framesDirectory);
    
    char** ExtractAsArray(int* framesAmount);
    ArrayList<char*>* ExtractAsList();
    
    ArrayList<ATexture*>* ExtractAsTextures();
    
    SpriteAnimation* ExtractAsAnimation(const char* name = NULL);
    
private:
    const char* currentDirectory; // Null if directory not loaded
    ARenderer* renderer; // Can be null if no need to manage textures
    
    bool DirectoryContainsManifest();
    
    ArrayList<ATexture*>* CreateFromSpritesheet();
};