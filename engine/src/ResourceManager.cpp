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

}

Resource* ResourceManager::AddFile(const char* filePath)
{
    return this->AddFile(filePath, filePath);
}

Resource* ResourceManager::AddFile(const char* filePath, const char* resourceName)
{
    FILE* found = fopen(filePath, "rb");

    if (found)
    {
        Resource* newRes = new Resource();
        newRes->name = new char[strlen(resourceName)];
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
    this->resourceRoots->push_back(rootFolderPath);
}

void ResourceManager::AddPackageFile(const char* packageFile)
{
    this->packageFiles->push_back(packageFile);
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
    auto filesBegin = files->begin();
    auto filesEnd = files->end();
    while (filesBegin != filesEnd)
    {
        Resource* res = (Resource*)*filesBegin;

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
