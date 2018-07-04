#include "Filesystem/XFile.h"
#include "libtech/pathutils.h"
#include "libtech/sysutils.h"

XFile::XFile()
{
    FilePath = NULL;
    FileName = NULL;
    FileExt = NULL;
    ParentDirectoryPath = NULL;

    loadedPath = NULL;
    handle = NULL;

#ifdef WIN32
    winFileHandle = INVALID_HANDLE_VALUE;
#endif
}

XFile::XFile(const char* filePath) : XFile()
{
    this->Open(filePath);
}

XFile::~XFile()
{

}

void XFile::Open(const char* path)
{
#ifdef WIN32
    winFileHandle = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (winFileHandle == INVALID_HANDLE_VALUE)
    {
        FilePath = NULL;
        FileName = NULL;
        FileExt = NULL;
        ParentDirectoryPath = NULL;

        Size = 0;

        return;
    }

    this->SetSize();
    this->AssignFileNames();

#endif
}

uint8_t* XFile::Read(size_t* length)
{
    if (this->IsValid() == false)
    {
        *length = 0;
        return NULL;
    }

    uint8_t* data = new uint8_t[this->Size];

#ifdef WIN32

    DWORD readBytes = 0;
    DWORD bytesToRead = (DWORD)this->Size; // Cutting the upper 32 bits, TODO
    BOOL res = ReadFile(
        winFileHandle,
        data,
        bytesToRead,
        &readBytes,
        NULL
    );

    if (res && bytesToRead == readBytes)
    {
        *length = this->Size;
        return data;
    }
    else
    {
        DWORD err = GetLastError();

        print_win32_error(err);
    }

#endif

    return NULL;
}

size_t XFile::Write(uint8_t* data, size_t length)
{
    return 0;
}

bool XFile::IsValid()
{
    return FilePath != NULL;
}

void XFile::AssignFileNames()
{
    FilePath = loadedPath;

    FileName = get_file_name(loadedPath);
    FileExt = get_file_extension(loadedPath);
    ParentDirectoryPath = get_parent_directory_path(loadedPath);


}

void XFile::SetSize()
{
#ifdef WIN32
    LARGE_INTEGER sizeResult;
    BOOL res = GetFileSizeEx(winFileHandle, &sizeResult);
    
    if (res)
    {
        /* The LARGE_INTEGER type changes based on the 32 or 64 bit architecture
        * being compiled. If on 64 bit we must use the .QuadPart to get the 64 bit
        * type. On 32bit the value is split in .LowPart and .HighPart. For now to
        * support all archs let's chop the upper 32 bits of the size and max out
        * at 4GB files. */
        this->Size = sizeResult.LowPart;
    }
    else
    {
        // TODO : Log
        this->Size = 0;
    }
#endif

    this->Size = 0;
}
