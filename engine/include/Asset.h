#pragma once

#include "core.h"

#include <stdint.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#define LARGE_FILE_MMAP_TRESH (1024*1024*10)// 10MB
#define LARGE_FILE_MMAP_LIMIT (1024*1024*1024*4) // 4GB

/**
 * \brief Type of an Asset.
 *
 * The values here are the only supported types of Asset. This is so
 * each type of asset can be properly understood by the engine.
 */
enum Asset_Type
{
    AT_UNKNOWN,
    AT_IMAGE,       /* .png .jpg .tga   */
    AT_FONT,        /* .ttf .otf        */
    AT_PACKAGE,     /* .pak             */
    AT_CONFIG       /* .xml .json .ini  */
};

/**
 * \brief Asset container class.
 *
 * This type is used to contain a loaded data. The data is typed with the
 * Asset_Type so we can assert and identify the binary content.
 */
class ENGINE_CLASS Asset
{
public:
    Asset();
    ~Asset();

    Asset_Type type;

    bool IsLoaded;
    char* name; // Friendly name
    const char* path; // Full path, may be relative
    uint64_t size;
    void* data;

    /**
     * \brief Load data from a file.
     *
     * \param path - File path to load.
     */
    void LoadData(const char* path);

    /**
     * \brief Get the content of the Asset.
     *
     * The length of the data returned is the size property of this
     * object.
     *
     * \return void* - Binary content.
     */
    void* GetData();

    /**
     * \brief Get a segment of data from the asset's content.
     *
     * \param start - Start address to read
     * \param end - End address to read.
     * \param readBytes - OUT To be supplied a pointer to drop the data to.
     *
     * \remark Not implemented yet.
     */
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