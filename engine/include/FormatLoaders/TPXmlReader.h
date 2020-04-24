#pragma once

#include <libtech/arraylist.h>

#include "core.h"

/**
 * Image entry inside a Texture Packer XML
 */
class ENGINE_CLASS TPXmlEntry
{
public:
    TPXmlEntry();
    ~TPXmlEntry();

    // Normal Attributes
    char* name;
    int x;
    int y;
    int w;
    int h;

    // Offset, if trimmed
    int oX;
    int oY;
    int oW;
    int oH;

    // Is 'y' if rotated. Rotation not supported so only need to check it's 0
    char r;
};

/**
 * Spritesheet information from a Texture Packer XML.
 */
class ENGINE_CLASS TPXmlHeader
{
public:
    TPXmlHeader();
    ~TPXmlHeader();

    char* imagePath;
    int width;
    int height;
};

/**
 * Parser class for a TexturePacker spritesheet XML. Can return an entry of each
 * image in the spritesheet or just return all images path to get their names.
 */
class ENGINE_CLASS TPXmlReader
{
public:
    TPXmlReader(const char* path);
    ~TPXmlReader();

    /**
     * Parse the TexturePacker .XML file and returns an entry for each sprite.
     * If the 'outHeaderInfo' parameter is provided, the header structure will
     * be filled with the TextureAtlas information from the xml.
     */
    ArrayList<TPXmlEntry*>* ReadEntries(TPXmlHeader* outHeaderInfo = NULL);

    /**
     * Extracts the file name of each sprite in the XML.
     */
    ArrayList<char*>* GetFileNames();

private:
    const char* loadedPath;
};