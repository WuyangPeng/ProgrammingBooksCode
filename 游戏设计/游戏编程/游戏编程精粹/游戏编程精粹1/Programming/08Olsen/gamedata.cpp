/* Copyright (C) John Olsen, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) John Olsen, 2000"
 */
#include <memory.h>
#include <stdio.h>

#ifndef TRUE
    #define TRUE 1
#endif
#ifndef FALSE
    #define FALSE 0
#endif

class GameData
{
public:
    bool Save(char* fileName);
    bool Load(char* fileName);
    bool BufferedLoad(char* fileName);
    // Add accessors to get to your game data.
private:
    // Only open one file at a time.
    // 一次只打开一个文件
    static FILE* fileDescriptor;
    // Game data goes here.
    // 游戏数据
    int data[1000];  // Replace this with your data format. 使用你自己的数据格式替换这个字段
};

bool GameData::Save(char* fileName)
{
    fopen_s(&fileDescriptor, fileName, "wb");
    if (fileDescriptor)
    {
        fwrite(this, sizeof(GameData), 1, fileDescriptor);
        fclose(fileDescriptor);
        // Report success writing the file.
        // 报告写文件成功
        return TRUE;
    }
    else
    {
        // Report an error writing the file.
        // 报告写文件失败
        return FALSE;
    }
}

bool GameData::Load(char* fileName)
{
    // Open the file for reading.
    // 以读模式打开文件
    fopen_s(&fileDescriptor, fileName, "rb");
    if (fileDescriptor)
    {
        fread(this, sizeof(GameData), 1, fileDescriptor);
        fclose(fileDescriptor);
        // Report success reading the file.
        // 报告读取文件成功 
        return TRUE;
    }
    else
    {
        // Report an error reading the file.
        // 报告读取文件错误
        return FALSE;
    }
}

// Check your hardware to see what size of blocks it reads.
// Put that value into this define.
// 检查你的硬件中一次读取块的大小
// 将值放在这个定义中
#define READ_GRANULARITY 2048

bool GameData::BufferedLoad(char* fileName)
{
    // Make sure there is room in the read buffer.
    // This could be made smaller to match the
    // known read size by making it a multiple of the
    // READ_GRANULARITY, but this way is a bit faster.
    // 确认读缓冲区有足够空间
    // 如果使用READ_GRANULARITY的倍数，使用的空间会小一些；但下面的方法会更快一点
    char* tempBuffer = new char[sizeof(GameData) + READ_GRANULARITY];
    if (!tempBuffer)
    {
        // Could not allocate the buffer.
        // Return an error code.
        // 不能分配缓冲区，返回错误代码
        return FALSE;
    }
    fopen_s(&fileDescriptor, fileName, "rb");
    if (fileDescriptor)
    {
        fread(tempBuffer, sizeof(GameData), 1, fileDescriptor);
        fclose(fileDescriptor);
        memcpy(this, tempBuffer, sizeof(GameData));
        delete tempBuffer;
        // Report success reading the file.
        // 报告读文件成功
        return TRUE;
    }
    else
    {
        delete tempBuffer;
        // Report an error reading the file.
        // 报告读文件错误
        return FALSE;
    }
}
