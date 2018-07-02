#pragma once


#include "core.h"
#include <list>
#include <tuple>
#include <stdint.h>

// Container for the binary data of an asset.
// Assets can be any file that the game will need, PNG's, font files, config files
// An instance of a resource should be the only copy of the binary data.
// Resources can be found by name from the ResourceManager.
struct Resource
{
    const char* name; // Name is owned by the Resource class.
    size_t length;
    uint8_t* data;
};

/**
 * The ResourceManager is in charge of loading data from sources like the disk
 * or from the network. Resources must be added to the manager before they can
 * be loaded. Resources are given a name when they are added, this name is used
 * when referencing the asset. 
 *
 * The ResourceManager owns the data and it will be freed when the destructor
 * is called.
 */
class ENGINE_CLASS ResourceManager
{
public:
    ResourceManager();
    virtual ~ResourceManager();
    
    /**
     * Load a resource into the manager. This will load the selected file from disk.
     * The resource will be available when calling GetResource(char*).
     */
    Resource* AddFile(const char* filePath);
    Resource* AddFile(const char* filePath, const char* resourceName);

    /**
     * Add a searchable path used when calling GetResource(char*).
     */
    void AddAssetRoot(const char* rootFolderPath);

    /**
     * Add a PAK file that will be searched when calling GetResource(char*).
     */
    void AddPackageFile(const char* packageFile);
    
    /**
     * Find a resource from the manager's stored resources. Data needs to be added
     * individually by AddFile or search roots need to be added.
     */
    Resource* GetResource(const char* name);

private:
    // Places where the manager will look for data to create resources
    std::list<const char*>* files; // Individual files added to the manager
    std::list<const char*>* resourceRoots; // Resource root folders
    std::list<const char*>* packageFiles; // PAK files

    // Once resources are found and created, a copy of the data will be here.
    // A single copy of a piece of data per resource in that list.
    std::list<Resource*>* resourceCache;
};