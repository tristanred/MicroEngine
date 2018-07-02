#pragma once

#include "core.h"

#include <stdint.h>
#include <stdio.h>

#ifdef WIN32

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")

#endif

class ENGINE_CLASS XFile
{
public:
    XFile();
    XFile(const char* filePath);
    ~XFile();
    
    const char* FilePath;
    const char* FileName;
    const char* FileExt;
    const char* ParentDirectoryPath;

    size_t Size;
    
    void Open(const char* path);
    
    uint8_t* Read(size_t* length);
    size_t Write(uint8_t* data, size_t length);

    bool IsValid();
    
    void AssignFileNames();
private:
    char* loadedPath;

    FILE* handle;

    void SetSize();

#ifdef WIN32
    HANDLE winFileHandle;
#endif
};