#include "Filesystem/XFile.h"
#include "libtech/pathutils.h"

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

}
