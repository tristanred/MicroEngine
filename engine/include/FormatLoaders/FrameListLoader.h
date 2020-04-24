#pragma once

class SpriteAnimation;
class ARenderer;
class ATexture;

#include <libtech/arraylist.h>

#include "core.h"

/**
 * This loader is used to generate frame information from a file or folder.
 *
 * This class is loaded with custom logic to support different formats of
 * frame-packing. There are 2 basic modes that the class will work with : File
 * mode and Directory mode.
 *
 * File Mode :
 * If pass a path to a file, the frame loader expects the file to a descriptor
 * file to a list of frames. The only supported format right now is Texture
 * Packer generic XML format.
 *
 * Directory mode :
 * In this mode, the loader tries a few different strategies. First it checks
 * if there is a "directory manifest" in the folder. A manifest is an XML file
 * called the name of the directory + .xml. This file contains the list of files
 * in that directory (or subdirectories) to load and special instructor for that
 * texture. The manifest XML format is not defined yet.
 * If there is no manifest file, it just loads all images in that directory.
 *
 * The Loader can return the information in a few different ways. Some of the
 * ways are more involved than others and requires help from the Renderer. If
 * there is a need to create frames, a reference to a Renderer will be required
 * in the constructor.
 */
class ENGINE_CLASS FrameListLoader
{
public:
    FrameListLoader(ARenderer* renderer = NULL);
    FrameListLoader(const char* framesPath, ARenderer* renderer = NULL);
    ~FrameListLoader();

    /**
     * Target a new path for extraction.
     */
    void Open(const char* path);

    /**
     * Extract the path of each images of the path. If the path is a file,
     * it extracts the image names from the spritesheet. If the path is a
     * directory it will extract the file names of the directory/
     */
    char** ExtractAsArray(int* framesAmount);

    /**
     * Same as ExtractAsArray but returned as an ArrayList.
     */
    ArrayList<char*>* ExtractAsList();

    /**
     * Extract a texture for each image of the path. Need to have a reference
     * to a renderer to create the textures.
     */
    ArrayList<ATexture*>* ExtractAsTextures();

    /**
     * Extracts the textures and builds a SpriteAnimation. Can optionally
     * give a name to the animation.
     */
    SpriteAnimation* ExtractAsAnimation(const char* name = NULL);

private:
    const char* currentPath;  // Null if directory not loaded
    ARenderer* renderer;      // Can be null if no need to manage textures

    bool DirectoryContainsManifest();

    ArrayList<ATexture*>* CreateFromSpritesheet();
};