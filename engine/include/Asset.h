#pragma once

#include "core.h"

#include <stdint.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#define LARGE_FILE_MMAP_TRESH (1024*1024*10)// 10MB
#define LARGE_FILE_MMAP_LIMIT ((1024*1024*1024*4)-1) // 4GB

enum Asset_Type
{
    AT_UNKNOWN,
    AT_IMAGE,       /* .png .jpg .tga   */
    AT_FONT,        /* .ttf .otf        */
    AT_PACKAGE,     /* .pak             */
    AT_CONFIG       /* .xml .json .ini  */
};

class ENGINE_CLASS Asset
{
public:
    Asset();
    ~Asset();
    
    Asset_Type type;
    
    bool IsLoaded;
    const char* path;
    uint64_t size;
    void* data;
    
    void LoadData(const char* path);
    
    void* GetData();
    
    void* GetBlock(uint64_t start, uint64_t end, uint64_t* readBytes);
private:
    
    Asset_Type DetermineAssetType(const char* assetPath);
    
    bool IsMemoryMapped;
    bool CanMemoryMapAsset(uint64_t candidateSize);

#ifdef _WIN32
    HANDLE hAssetFile;
    HANDLE hFileMap;
#endif

};