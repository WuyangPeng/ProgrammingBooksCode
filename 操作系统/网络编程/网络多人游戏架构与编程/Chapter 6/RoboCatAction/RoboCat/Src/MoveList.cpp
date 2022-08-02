#include <RoboCatPCH.h>

const Move& MoveList::AddMove(const InputState& inInputState, float inTimestamp)
{
    //first move has 0 time. it's okay, it only happens once
    // ��һ����0time�� û��ϵ����ֻ�ᷢ��һ��
    float deltaTime = mLastMoveTimestamp >= 0.f ? inTimestamp - mLastMoveTimestamp : 0.f;

    mMoves.emplace_back(inInputState, inTimestamp, deltaTime);

    mLastMoveTimestamp = inTimestamp;

    return mMoves.back();
}

bool MoveList::AddMove(const Move& inMove)
{
    //adjust the delta time and then place!
    // ����ʱ�䣬Ȼ�����ʱ�䣡
    float timeStamp = inMove.GetTimestamp();
    float deltaTime = mLastMoveTimestamp >= 0.f ? timeStamp - mLastMoveTimestamp : 0.f;
    mLastMoveTimestamp = timeStamp;
    mMoves.emplace_back(inMove.GetInputState(), timeStamp, deltaTime);
    return true;
}

void MoveList::RemovedProcessedMoves(float inLastMoveProcessedOnServerTimestamp)
{
    while (!mMoves.empty() && mMoves.front().GetTimestamp() <= inLastMoveProcessedOnServerTimestamp)
    {
        mMoves.pop_front();
    }
}
