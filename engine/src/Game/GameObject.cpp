#include "Game/GameObject.h"

#include <GameEngine.h>
#include <GameModule.h>

#include "libtech/mytime.h"

GameObject::GameObject(GameEngine* engine)
{
    this->engine = engine;
}

GameObject::~GameObject() {}

void GameObject::Update(unsigned int deltaTime)
{
    this->lastUpdateTime = get_a_ticks();
}

GameEngine* GameObject::GetEngine()
{
    return this->engine;
}

long GameObject::DeltaTime()
{
    return this->engine->GetDeltaTime();
}
