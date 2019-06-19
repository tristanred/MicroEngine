#include "TextureTestModule.h"

#include "Asset.h"
#include "ResourceManager.h"
#include "Viewport.h"
#include "Controls/CButton.h"
#include "Controls/CLabel.h"
#include <libtech/arraylist.h>
#include "Rendering/ATexture.h"
#include <Input/AKeyboard.h>

TextureTestModule::TextureTestModule(GameEngine* engine) : GameModule(engine)
{
    this->Test = new RenderableObject(engine);
    this->Test->SetTexture("assets/engine/TestTexture.png");

    this->AttachRenderable(this->Test);
}

TextureTestModule::~TextureTestModule()
{
    this->DestroyObject(this->Test);
}

void TextureTestModule::Update(unsigned int deltaTime)
{
    GameModule::Update(deltaTime);
}

void TextureTestModule::Draw(ARenderer* renderer)
{
    GameModule::Draw(renderer);
}
