#include "AText.h"

AText::AText(GameEngine* engine) : ARenderable(engine)
{
    LogTrace("AText::AText");
}

AText::~AText()
{
    LogTrace("AText::~AText");
}
