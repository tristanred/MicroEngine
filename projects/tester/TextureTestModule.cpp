#include "TextureTestModule.h"

#include "Asset.h"
#include "ResourceManager.h"
#include "Viewport.h"
#include "Controls/CButton.h"
#include "Controls/CLabel.h"
#include <libtech/arraylist.h>
#include "ATexture.h"
#include <Input/AKeyboard.h>

TextureTestModule::TextureTestModule(GameEngine* engine) : GameModule(engine)
{
    toggle = false;

    //this->TextureTest = this->CreateTexture();
    //this->TextureTest->SetSolidColor(FSize(100, 100), 0xFFFFFF00);
    this->TextureTest = this->CreateTexture("assets/engine/Enabled.png");
    
    this->SpriteTest = this->CreateSprite();
    this->SpriteTest->SetTexture(this->TextureTest);
    this->SpriteTest->SetPosition(50, 50);
}

TextureTestModule::~TextureTestModule()
{
}

void TextureTestModule::Update(unsigned int deltaTime)
{
    GameModule::Update(deltaTime);

    if(this->GetEngine()->Keyboard->IsKeyClicked(Key::Space))
    {
        if(toggle)
        {
            this->SpriteTest->SetSize(128, 128);
        }
        else
        {
            this->SpriteTest->SetSize(500, 500);
        }

        toggle = !toggle;
    }

}

void TextureTestModule::Draw(ARenderer* renderer)
{
    //this->GetRenderer()->DrawTexture(this->TextureTest, 30, 30);
    //this->GetRenderer()->Draw(TextTest);
    this->GetRenderer()->Draw(SpriteTest);
}
