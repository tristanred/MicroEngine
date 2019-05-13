#include "Asset.h"

#include <libtech/pathutils.h>
#include <libtech/sysutils.h>
#include <string.h>

#if defined(linux) || defined(__APPLE__)
#include <libtech/binreader.h>
#endif

Asset::Asset()
{
    type = AT_UNKNOWN;
    IsLoaded = false;
    IsMemoryMapped = false;
    path = NULL;
    size = 0;
    data = NULL;

#ifdef _WIN32
    this->hAssetFile = INVALID_HANDLE_VALUE;
    this->hFileMap = INVALID_HANDLE_VALUE;
#endif
}

Asset::~Asset()
{
#ifdef _WIN32
    if(this->hFileMap != INVALID_HANDLE_VALUE)
    {
        CloseHandle(this->hFileMap);
    }

    if(hAssetFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hAssetFile);
    }
#endif
}

void Asset::LoadData(const char* path)
{
    char* safepath = new char[strlen(path) + 1];
    sanitize_path_slashes(path, safepath);

#ifdef _WIN32

    hAssetFile = CreateFileA(
        path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if(hAssetFile == INVALID_HANDLE_VALUE)
    {
        print_last_win32_error();

        IsLoaded = NULL;
        path = NULL;
        size = 0;
        data = NULL;

        return;
    }

    LARGE_INTEGER size;
    size.QuadPart = 0;
    BOOL res = GetFileSizeEx(hAssetFile, &size);
    if(res == FALSE)
    {
        print_last_win32_error();

        return;
    }

    char* assetExt = get_file_extension(path);

    if(strcmp(path, ".pak") != -1 && this->CanMemoryMapAsset(this->size))
    {
        delete(assetExt); // Ugh....

        hFileMap = CreateFileMappingA(
            hAssetFile,
            NULL,
            FILE_SHARE_READ,
            0,
            0,
            NULL);

        if(hFileMap == NULL)
        {
            print_last_win32_error();

            return;
        }

        data = MapViewOfFile(
            hFileMap,
            FILE_MAP_READ,
            0,
            0,
            0);

        if(data == NULL)
        {
            print_last_win32_error();

            return;
        }

        this->type = AT_PACKAGE;
        this->IsMemoryMapped = true;
        this->IsLoaded = true;
        this->path = path;
        this->size = size.QuadPart;
    }
    else
    {
        data = new uint8_t[size.QuadPart];
        DWORD readBytes = 0;
        BOOL res = ReadFile(
            hAssetFile,
            data,
            size.LowPart,
            &readBytes,
            NULL
        );

        if (res == FALSE)
        {
            print_last_win32_error();

            return;
        }

        this->type = this->DetermineAssetType(path);
        this->IsMemoryMapped = false;
        this->IsLoaded = true;
        this->path = path;
        this->size = size.QuadPart;
    }
#elif defined(linux) || defined(__APPLE__)

    size_t size;
    this->data = getfilebytes(safepath, &size);

    if(this->data != NULL)
    {
        this->type = this->DetermineAssetType(safepath);
        this->IsMemoryMapped = false;
        this->IsLoaded = true;
        this->path = safepath;
        this->size = size;
    }
#endif
}

void* Asset::GetData()
{
    // TODO : For not, no lazy loading. We intake the whole data when calling
    // LoadData. Could eventually just open the file in LoadData and retrieve
    // the contents here. In that case, set this->data as private.
    return data;
}

void* Asset::GetBlock(uint64_t start, uint64_t end, uint64_t* readBytes)
{
    // Not implemented yet, read the whole data or nothing.
    *readBytes = 0;
    return NULL;
}

Asset_Type Asset::DetermineAssetType(const char* assetPath)
{
    char* assetExt = get_file_extension(assetPath);

    if(strcmp(assetExt, ".png") == 0)
    {
        return AT_IMAGE;
    }
    else if(strcmp(assetExt, ".jpg") == 0)
    {
        return AT_IMAGE;
    }
    else if(strcmp(assetExt, ".tga") == 0)
    {
        return AT_IMAGE;
    }
    else if(strcmp(assetExt, ".ttf") == 0)
    {
        return AT_FONT;
    }
    else if(strcmp(assetExt, ".otf") == 0)
    {
        return AT_FONT;
    }
    else if(strcmp(assetExt, ".pak") == 0)
    {
        return AT_PACKAGE;
    }
    else if(strcmp(assetExt, ".xml") == 0)
    {
        return AT_CONFIG;
    }
    else if(strcmp(assetExt, ".json") == 0)
    {
        return AT_CONFIG;
    }
    else if(strcmp(assetExt, ".ini") == 0)
    {
        return AT_CONFIG;
    }

    return AT_UNKNOWN;
}


bool Asset::CanMemoryMapAsset(uint64_t candidateSize)
{
    // MM assets only on windows for now.
#ifdef _WIN32
    if(candidateSize >= LARGE_FILE_MMAP_TRESH &&
       candidateSize < LARGE_FILE_MMAP_LIMIT)
    {
        return true;
    }
#endif

    return false;
}
