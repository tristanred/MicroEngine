#pragma once

#include <stdint.h>
#include <stdio.h>

#include "core.h"

#ifdef _WIN32

#include <stdio.h>
#include <strsafe.h>
#include <tchar.h>
#include <windows.h>
#pragma comment(lib, "User32.lib")

#endif

class ENGINE_CLASS XFile
{
public:
    XFile();
    XFile(const char* filePath);
    ~XFile();

    // These paths are set after loading the file. They are helper paths
    // calculated from the main FilePath.
    const char* FilePath;
    const char* FileName;
    const char* FileExt;
    const char* ParentDirectoryPath;

    // Size of the loaded file. Size of 0 usually indicate that the file does
    // not exist or is invalid. Size can be 0 if we open a new file for
    // writting.
    size_t Size;

    // Open the file but does not read anything. This will check file
    // permissions, ensure that the file exists and is a valid target.
    void Open(const char* path);

    // IO functions
    uint8_t* Read(size_t* length);
    size_t Write(uint8_t* data, size_t length);

    // Check if the file has opened correctly and can be used.
    // Basically amounts to checking if the FilePath isn't NULL.
    bool IsValid();

private:
    // File path that is currently loaded. Set to NULL if the file isn't
    // correct. If this path is set, it means that the target file exists and
    // everything checks out. If loadedPath is NULL, the file is not opened or
    // invalid.
    char* loadedPath;

    // Get the file size from the file that is opened.
    void SetSize();
    // Decompose the loaded filename into parts and assign them to the
    // helper paths above.
    void AssignFileNames();

#ifdef WIN32
    // Set to INVALID_HANDLE_VALUE by default.
    HANDLE winFileHandle;
#endif
};