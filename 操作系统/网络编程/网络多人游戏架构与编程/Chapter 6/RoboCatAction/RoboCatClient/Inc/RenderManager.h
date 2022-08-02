#pragma once

#include "SpriteComponent.h"

//I take care of rendering things!

class RenderManager
{
public:
    static void StaticInit();
    static std::unique_ptr<RenderManager> sInstance;

    void Render();
    void RenderComponents();

    //vert inefficient method of tracking scene graph...
    // ׷�ٳ���ͼ��vert��Ч����...
    void AddComponent(SpriteComponent* inComponent);
    void RemoveComponent(SpriteComponent* inComponent);
    int GetComponentIndex(SpriteComponent* inComponent) const;

private:
    RenderManager();

    //this can't be only place that holds on to component- it has to live inside a GameObject in the world
    // �ⲻ���Ƿ�������ĵط��������������������ϵ�GameObject�ڲ�
    vector<SpriteComponent*> mComponents;

    SDL_Rect mViewTransform;
};
