#include "ResourceManager.h"

#include <stdio.h>
#include <string.h>

ResourceManager::ResourceManager()
{
    files = new std::list<const char*>();
    resourceRoots = new std::list<const char*>();
    packageFiles = new std::list<const char*>();
    resourceCache = new std::list<Resource*>();
}

ResourceManager::~ResourceManager()
{
    auto filesBegin = files->begin();
    auto filesEnd = files->end();
    while(filesBegin != filesEnd)
    {
        const char* filePath = *filesBegin;

        delete(filePath);

        filesBegin++;
    }
    files->clear();
    delete(files);

    auto rootsBegin = resourceRoots->begin();
    auto rootsEnd = resourceRoots->end();
    while(rootsBegin != rootsEnd)
    {
        const char* rootPath = *rootsBegin;
        
        delete(rootPath);

        rootsBegin++;
    }
    resourceRoots->clear();
    delete(resourceRoots);

    auto pakFileBegin = packageFiles->begin();
    auto pakFileEnd = packageFiles->end();
    while(pakFileBegin != pakFileEnd)
    {
        const char* pakFilePath = *pakFileBegin;
        
        delete(pakFilePath);

        pakFileBegin++;
    }
    packageFiles->clear();
    delete(packageFiles);

    auto resourcesBegin = resourceCache->begin();
    auto resourcesEnd = resourceCache->end();
    while(resourcesBegin != resourcesEnd);
    {
        Resource* res = *resourcesBegin;
        
        delete(res);

        resourcesBegin++;
    }
    resourceCache->clear();
    delete(resourceCache);
}

Resource* ResourceManager::AddFile(const char* filePath)
{
    return this->AddFile(filePath, filePath);
}

Resource* ResourceManager::AddFile(const char* filePath, const char* resourceName)
{
    // Check if we already have the resource in our cache.
    auto resBegin = resourceCache->begin();
    auto resEnd = resourceCache->end();
    while(resBegin != resEnd)
    {
        Resource* res = *resBegin;

        if(strcmp(res->name, resourceName) == 0)
        {
            return res;
        }

        resBegin++;
    }

    FILE* found = fopen(filePath, "rb");

    if (found)
    {
        Resource* newRes = new Resource();
        newRes->name = new char[strlen(resourceName)+1];
        strcpy((char*)newRes->name, resourceName);

        long fileSize = 0;
        fseek(found, 0, SEEK_END);
        fileSize = ftell(found);
        fseek(found, 0, SEEK_SET);

        newRes->length = fileSize;
        newRes->data = new uint8_t[fileSize];
        size_t readBytes = fread(newRes->data, 1, fileSize, found);

        this->resourceCache->push_back(newRes);

        fclose(found);

        return newRes;
    }

    return NULL;
}

void ResourceManager::AddAssetRoot(const char* rootFolderPath)
{
    char* rootPathCopy = new char[strlen(rootFolderPath)+1];
    strcpy(rootPathCopy, rootFolderPath);

    this->resourceRoots->push_back(rootPathCopy);
}

void ResourceManager::AddPackageFile(const char* packageFile)
{
    char* pakPathCopy = new char[strlen(packageFile) + 1];
    strcpy(pakPathCopy, packageFile);

    this->packageFiles->push_back(pakPathCopy);
}

// Temp function signature
// This function returns the full path of a file under the 'folder' directory
// Returns NULL if none found.
char* find_subdir_file(char* folder, const char* filePath)
{
    return NULL;
}

Resource* ResourceManager::GetResource(const char* name)
{
    // Finding a resource is a multi-step process
    // First we check in the list of assets we have added
    auto filesBegin = resourceCache->begin();
    auto filesEnd = resourceCache->end();
    while (filesBegin != filesEnd)
    {
        Resource* res = *filesBegin;

        if (strcmp(res->name, name) == 0)
        {
            return res;
        }

        filesBegin++;
    }

    // Then check in the asset roots for any files that matches the name query
    // The name we search for could be a full path
    auto rootsBegin = resourceRoots->begin();
    auto rootsEnd = resourceRoots->end();
    while (rootsBegin != rootsEnd)
    {
        char* rootObject = (char*)*rootsBegin;

        const char* foundPathName = find_subdir_file(rootObject, name);

        if (foundPathName != NULL)
        {
            Resource* newRes = this->AddFile(foundPathName);

            return newRes;
        }

        rootsBegin++;
    }

    // Then we look inside the PAK files we have loaded
    auto pakBegin = packageFiles->begin();
    auto pakEnd = packageFiles->end();
    while (pakBegin != pakEnd)
    {
        // PAK files not implemented yet.

        pakBegin++;
    }

    return NULL;
}
