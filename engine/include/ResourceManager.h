#pragma once

class Asset;

#include <stdint.h>

#include <list>
#include <tuple>

#include "core.h"

/**
 * \brief Resource loader and handler for the engine.
 *
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
     * \brief Load a resource into the manager.
     *
     * This overlod does not specify a name to give to the resource. The name
     * given will be automatically created from the file name. Usually the name
     * will be filename without extension.
     *
     * This will load the selected file from disk. The resource will be
     * available when calling GetResource(char*).
     *
     * \param filePath - File path to load.
     *
     * \return Asset - Asset object with the data.
     */
    Asset* AddFile(const char* filePath);

    /**
     * \brief Load a resource into the manager and set a name for it.
     *
     * \param filePath - File path to load.
     * \param resourceName - Name given to the new resource.
     *
     * \return Asset - Asset object with the data.
     */
    Asset* AddFile(const char* filePath, const char* resourceName);

    /**
     * \brief Add a searchable path used when calling GetResource(char*).
     *
     * This directory will be recursively searched when looking for an asset
     * that isn't found in the immediate files list.
     *
     * \param rootFolderPath - Path to a directory.
     */
    void AddAssetRoot(const char* rootFolderPath);

    /**
     * \brief Add a PAK file that will be searched when calling
     * GetResource(char*).
     *
     * \param packageFile - File path of the package file.
     */
    void AddPackageFile(const char* packageFile);

    /**
     * \brief Find a resource by name.
     *
     * Returns NULL if nothing is found.
     *
     * Find a resource from the manager's stored resources. Data needs to be
     * added individually by AddFile or search roots need to be added.
     *
     * \param name - Name identifier of the resource to find.
     *
     * \return Asset - Asset found.
     */
    Asset* GetResource(const char* name);

private:
    // Places where the manager will look for data to create resources
    std::list<const char*>* files;  // Individual files added to the manager
    std::list<const char*>* resourceRoots;  // Resource root folders
    std::list<const char*>* packageFiles;   // PAK files

    // Once resources are found and created, a copy of the data will be here.
    // A single copy of a piece of data per resource in that list.
    std::list<Asset*>* resourceCache;
};