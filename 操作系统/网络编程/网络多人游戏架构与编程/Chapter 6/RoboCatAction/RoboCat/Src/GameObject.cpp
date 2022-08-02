#include <RoboCatPCH.h>

GameObject::GameObject()
    : mIndexInWorld(-1),
      mCollisionRadius(0.5f),
      mDoesWantToDie(false),
      mRotation(0.f),
      mNetworkId(0),
      mColor(Colors::White),
      mScale(1.0f)
{
}

void GameObject::Update()
{
    //object don't do anything by default...
    // 对象默认不执行任何操作...
}

Vector3 GameObject::GetForwardVector() const
{
    //should we cache this when you turn?
    // 转身时应该缓存吗？
    return Vector3(sinf(mRotation), -cosf(mRotation), 0.f);
}

void GameObject::SetNetworkId(int inNetworkId)
{
    //this doesn't put you in the map or remove you from it
    // 这不会将您放入地图或将您从地图中删除
    mNetworkId = inNetworkId;
}

void GameObject::SetRotation(float inRotation)
{
    //should we normalize using fmodf?
    // 我们应该使用fmodf进行归一化吗？
    mRotation = inRotation;
}
