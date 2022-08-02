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
    // һ��ֻ��һ���ļ�
    static FILE* fileDescriptor;
    // Game data goes here.
    // ��Ϸ����
    int data[1000];  // Replace this with your data format. ʹ�����Լ������ݸ�ʽ�滻����ֶ�
};

bool GameData::Save(char* fileName)
{
    fopen_s(&fileDescriptor, fileName, "wb");
    if (fileDescriptor)
    {
        fwrite(this, sizeof(GameData), 1, fileDescriptor);
        fclose(fileDescriptor);
        // Report success writing the file.
        // ����д�ļ��ɹ�
        return TRUE;
    }
    else
    {
        // Report an error writing the file.
        // ����д�ļ�ʧ��
        return FALSE;
    }
}

bool GameData::Load(char* fileName)
{
    // Open the file for reading.
    // �Զ�ģʽ���ļ�
    fopen_s(&fileDescriptor, fileName, "rb");
    if (fileDescriptor)
    {
        fread(this, sizeof(GameData), 1, fileDescriptor);
        fclose(fileDescriptor);
        // Report success reading the file.
        // �����ȡ�ļ��ɹ� 
        return TRUE;
    }
    else
    {
        // Report an error reading the file.
        // �����ȡ�ļ�����
        return FALSE;
    }
}

// Check your hardware to see what size of blocks it reads.
// Put that value into this define.
// ������Ӳ����һ�ζ�ȡ��Ĵ�С
// ��ֵ�������������
#define READ_GRANULARITY 2048

bool GameData::BufferedLoad(char* fileName)
{
    // Make sure there is room in the read buffer.
    // This could be made smaller to match the
    // known read size by making it a multiple of the
    // READ_GRANULARITY, but this way is a bit faster.
    // ȷ�϶����������㹻�ռ�
    // ���ʹ��READ_GRANULARITY�ı�����ʹ�õĿռ��СһЩ��������ķ��������һ��
    char* tempBuffer = new char[sizeof(GameData) + READ_GRANULARITY];
    if (!tempBuffer)
    {
        // Could not allocate the buffer.
        // Return an error code.
        // ���ܷ��仺���������ش������
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
        // ������ļ��ɹ�
        return TRUE;
    }
    else
    {
        delete tempBuffer;
        // Report an error reading the file.
        // ������ļ�����
        return FALSE;
    }
}
