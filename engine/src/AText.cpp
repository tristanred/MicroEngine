#include "AText.h"

AText::AText(ARenderer* renderer) : ARenderable(renderer)
{
    LogTrace("AText::AText");
}

AText::~AText()
{
    LogTrace("AText::~AText");
}
