#include <RoboCatPCH.h>

std::unique_ptr<World> World::sInstance;

void World::StaticInit()
{
    sInstance.reset(new World());
}

World::World()
{
}

void World::AddGameObject(GameObjectPtr inGameObject)
{
    mGameObjects.push_back(inGameObject);
    inGameObject->SetIndexInWorld(static_cast<int>(mGameObjects.size() - 1));
}

void World::RemoveGameObject(GameObjectPtr inGameObject)
{
    int index = inGameObject->GetIndexInWorld();

    int lastIndex = static_cast<int>(mGameObjects.size() - 1);
    if (index != lastIndex)
    {
        mGameObjects[index] = mGameObjects[lastIndex];
        mGameObjects[index]->SetIndexInWorld(index);
    }

    inGameObject->SetIndexInWorld(-1);

    mGameObjects.pop_back();
}

void World::Update()
{
    //update all game objects- sometimes they want to die, so we need to tread carefully...
    // 更新所有游戏对象——有时他们想死，所以我们需要小心行事...

    for (int i = 0, c = static_cast<int>(mGameObjects.size()); i < c; ++i)
    {
        GameObjectPtr go = mGameObjects[i];

        if (!go->DoesWantToDie())
        {
            go->Update();
        }
        //you might suddenly want to die after your update, so check again
        // 您可能会在更新后突然想死，所以请再次检查
        if (go->DoesWantToDie())
        {
            RemoveGameObject(go);
            go->HandleDying();
            --i;
            --c;
        }
    }
}