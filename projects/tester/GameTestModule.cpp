#include "GameTestModule.h"

#define MAX_BOX_COLOR 7
int currentColorIndex = 0;
uint32_t colorCycle[MAX_BOX_COLOR] = {
    0xFFFF0000,
    0xFF00FF00,
    0xFF0000FF,
    0xFFFFFF00,
    0xFFFF00FF,
    0xFF00FFFF,
    0xFFFF00FF
};

GameTestModule::GameTestModule(GameEngine* engine) : GameModule(engine)
{
    Box = this->CreateSprite();
    Box->SetSize(FSize(75, 75));

    BoxTexture = engine->Renderer->CreateTexture();
    BoxTexture->SetSolidColor(FSize(75, 75), 0xFFAA0000);

    Box->SetTexture(BoxTexture);

    ArialFont = this->CreateFont();
    ArialFont->LoadFontFile("assets/engine/arial.ttf");

    BoxText = this->CreateText();
    BoxText->SetFont(ArialFont);
    BoxText->SetText("BOX");
    BoxText->SetColor(0xFFFFFFFF);

    boxVelocity.x = 5;
    boxVelocity.y = 5;

    TimerText = this->CreateText();
    TimerText->SetFont(ArialFont);
    TimerText->SetText("0");
    TimerText->SetColor(0xFF000000);

    timer = new TickTimer(10000);
}

GameTestModule::~GameTestModule()
{

}

void GameTestModule::Update(unsigned int deltaTime)
{
    GameModule::Update(deltaTime);

    timer->Update(deltaTime);
    char timermsg[256];
    sprintf(timermsg, "%f %%", timer->GetCurrentPercentage() * 100);
    TimerText->SetText(timermsg);

    FPosition nextPos = Box->GetPosition();
    nextPos.X += boxVelocity.x;
    nextPos.Y += boxVelocity.y;

    FSize windowSize = GetEngine()->Renderer->GetWindowSize();
    if (nextPos.X + Box->GetSize().Width > windowSize.Width)
    {
        boxVelocity.x *= -1;
        nextPos.X = windowSize.Width - Box->GetSize().Width;
        Box->GetTexture()->FillColor(colorCycle[currentColorIndex % MAX_BOX_COLOR]);
        currentColorIndex++;
    }
    if (nextPos.X < 0)
    {
        boxVelocity.x *= -1;
        nextPos.X = 0;
        Box->GetTexture()->FillColor(colorCycle[currentColorIndex % MAX_BOX_COLOR]);
        currentColorIndex++;
    }
    if (nextPos.Y + Box->GetSize().Height > windowSize.Height)
    {
        boxVelocity.y *= -1;
        nextPos.Y = windowSize.Height - Box->GetSize().Height;
        Box->GetTexture()->FillColor(colorCycle[currentColorIndex % MAX_BOX_COLOR]);
        currentColorIndex++;
    }
    if (nextPos.Y < 0)
    {
        boxVelocity.y *= -1;
        nextPos.Y = 0;
        Box->GetTexture()->FillColor(colorCycle[currentColorIndex % MAX_BOX_COLOR]);
        currentColorIndex++;
    }
    
    Box->SetPosition(nextPos);

    FPosition textPosition = nextPos;
    textPosition.X += 12;
    textPosition.Y += 20;
    BoxText->SetPosition(textPosition);
}
