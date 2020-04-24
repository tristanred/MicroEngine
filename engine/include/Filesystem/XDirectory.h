#pragma once

class XFile;

#include <stdint.h>

#include <list>

#include "core.h"

class ENGINE_CLASS XDirectory
{
public:
    XDirectory();
    XDirectory(const char* folderPath);
    ~XDirectory();

    std::list<XFile*>* GetFiles(bool recursive = false);

private:
    // char* loadedPath;
};
