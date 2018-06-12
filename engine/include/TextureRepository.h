#pragma once

class ATexture;

#include "core.h"
#include <map>

/**
 * This class wraps a set of textures that can be searched by path
 * to re-use instances of textures. This class does not own the Texture
 * instances and will not call delete() on them once this class gets 
 * destroyed.
 */
class ENGINE_CLASS TextureRepository
{
public:
    TextureRepository();
    virtual ~TextureRepository();

    /**
     * Find a texture in the repository to see if a texture was already created
     * from the same path. Will return NULL if none is found.
     * \param filepath Path of the file to look for.
     */
    ATexture* FindTexture(const char* filepath);

    /**
     * Add a texture to the cache so FindTexture will return it.
     * \param texTexture to add
     */
    void CacheTexture(ATexture* tex);

    /**
     * Remove all the cache entries. This does not deallocate the textures.
     */
    void EmptyCache();

protected:
    std::map<const char*, ATexture*>* TextureList;
};