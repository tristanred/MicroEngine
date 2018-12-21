#pragma once

class XFile;

#include "core.h"

#include <stdint.h>
#include <list>

class ENGINE_CLASS XDirectory
{
public:
    XDirectory();
    XDirectory(const char* folderPath);
    ~XDirectory();
    
    std::list<XFile*>* GetFiles(bool recursive = false);
    
private:
    //char* loadedPath;
};
