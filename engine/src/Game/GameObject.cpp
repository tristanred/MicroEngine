#include "Game/GameObject.h"
#include "libtech/mytime.h"

GameObject::GameObject()
{
    this->Owner = NULL;
}

GameObject::~GameObject()
{

}

void GameObject::Setup(GameModule* currentModule)
{
    this->Owner = currentModule;
}

void GameObject::Update(unsigned int deltaTime)
{
    this->lastUpdateTime = get_a_ticks();
}

void GameObject::Draw()
{
    this->lastDrawTime = get_a_ticks();
}

GameEngine* GameObject::GetEngine()
{
    return this->Owner->GetEngine();
}

long GameObject::DeltaTime()
{
    return this->GetEngine()->GetDeltaTime();
}
