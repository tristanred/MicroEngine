#include "AText.h"

AText::AText(GameEngine* engine) : RenderableObject(engine)
{
    LogTrace("AText::AText");
}

AText::~AText()
{
    LogTrace("AText::~AText");
}
