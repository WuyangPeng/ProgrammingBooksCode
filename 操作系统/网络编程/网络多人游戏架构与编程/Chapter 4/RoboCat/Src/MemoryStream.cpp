#include <RoboCatPCH.h>

void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
    mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
    //handle realloc failure
    // �������·���ʧ��
    //...
    mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void* inData, size_t inByteCount)
{
    //make sure we have space...
    // ȷ�������пռ䡣
    uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
    if (resultHead > mCapacity)
    {
        ReallocBuffer(std::max(mCapacity * 2, resultHead));
    }

    //copy into buffer at head
    // ���Ƶ�ͷ���Ļ�����
    std::memcpy(mBuffer + mHead, inData, inByteCount);

    //increment head for next write
    // ��һ��д�������ͷ
    mHead = resultHead;
}

void InputMemoryStream::Read(void* outData, uint32_t inByteCount)
{
    uint32_t resultHead = mHead + inByteCount;
    if (resultHead > mCapacity)
    {
        //handle error, no data to read!
        //...
    }

    std::memcpy(outData, mBuffer + mHead, inByteCount);

    mHead = resultHead;
}