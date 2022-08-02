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
    // 追踪场景图的vert低效方法...
    void AddComponent(SpriteComponent* inComponent);
    void RemoveComponent(SpriteComponent* inComponent);
    int GetComponentIndex(SpriteComponent* inComponent) const;

private:
    RenderManager();

    //this can't be only place that holds on to component- it has to live inside a GameObject in the world
    // 这不仅是放置组件的地方，还必须生活在世界上的GameObject内部
    vector<SpriteComponent*> mComponents;

    SDL_Rect mViewTransform;
};
