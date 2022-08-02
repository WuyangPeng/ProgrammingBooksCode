#include "handle.h"
#include "handlemgr.h"

#include <Windows.h>
#include <string>

struct FileEntry
{
    std::string m_FileName;
    HANDLE m_FileHandle;  // 操作系统文件句柄
};

struct tagFile
{
};

typedef Handle<tagFile> HFile;
typedef HandleMgr<FileEntry, HFile> FileHandleMgr;

class FileMgr
{
    FileHandleMgr m_Mgr;

public:
    HFile OpenFile(const char* name);
    bool ReadFile(HFile file, void* out, size_t bytes);
    bool CloseFile(HFile file);

    // ...
};