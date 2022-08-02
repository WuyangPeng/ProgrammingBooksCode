#include <RoboCatPCH.h>

std::unique_ptr<GameObjectRegistry> GameObjectRegistry::sInstance;

void GameObjectRegistry::StaticInit()
{
    sInstance.reset(new GameObjectRegistry());
}

GameObjectRegistry::GameObjectRegistry()
{
}

void GameObjectRegistry::RegisterCreationFunction(uint32_t inFourCCName, GameObjectCreationFunc inCreationFunction)
{
    mNameToGameObjectCreationFunctionMap[inFourCCName] = inCreationFunction;
}

GameObjectPtr GameObjectRegistry::CreateGameObject(uint32_t inFourCCName)
{
    //no error checking- if the name isn't there, exception!
    // 没有错误检查——如果名称不存在，异常！
    GameObjectCreationFunc creationFunc = mNameToGameObjectCreationFunctionMap[inFourCCName];

    GameObjectPtr gameObject = creationFunc();

    //should the registry depend on the world? this might be a little weird
    //perhaps you should ask the world to spawn things? for now it will be like this
    // 注册表应取决于世界吗？ 这可能有点怪异，也许您应该要求世界产生事物？ 现在会是这样
    World::sInstance->AddGameObject(gameObject);

    return gameObject;
}