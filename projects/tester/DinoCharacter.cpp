#include "DinoCharacter.h"

DinoCharacter::DinoCharacter(GameEngine* engine) : GameObject(engine)
{
    this->DinoSprite = NULL;
}

DinoCharacter::~DinoCharacter()
{
    // this->GetEngine()->DestroyObject(this->DinoSprite);
}

void DinoCharacter::Setup(GameModule* currentModule)
{
    this->DinoSprite = currentModule->CreateSprite();
    this->DinoSprite->SetPosition(600, 0);
    this->DinoSprite->SetScale(6);

    /**
     * Current implementation needs :
     * We have 1 long strip of sprites
     * We need to split that strip and take some textures and generate
     * animations from them.
     *
     */
    auto textureStrip =
        currentModule->CreateTexture("assets/engine/dino/doux.png");

    // SplitTexture(int numberOfSplits) Only horizontal split
    // SplitTexture(int rows, int columns) Grid splitting
    // SplitTexture(FRectangle) Piece by piece splitting
    ArrayList<ATexture*>* splitted = textureStrip->SplitTexture(24);

    SpriteAnimation* idleAnim = SpriteAnimation::FromTextures(splitted, "0..6");
    idleAnim->SetName("Idle");

    SpriteAnimation* moveAnim =
        SpriteAnimation::FromTextures(splitted, "6..12");
    moveAnim->SetName("Move");

    SpriteAnimation* hurtAnim =
        SpriteAnimation::FromTextures(splitted, "12..24");
    hurtAnim->SetName("Hurt");

    this->DinoSprite->AddAnimation(idleAnim);
    this->DinoSprite->AddAnimation(moveAnim);
    this->DinoSprite->AddAnimation(hurtAnim);

    this->DinoSprite->Play("Idle", true, 10);
}

void DinoCharacter::Update(unsigned int deltaTime)
{
    this->DinoSprite->Update(deltaTime);
}
