#include <stdio.h>

#include <GameEngine.h>
#include "OverworldGameModule.h"

int main(int argc, char** argv)
{
    printf("Hello RPG.");

    GameEngine engine;
    engine.Initialize();

    auto mod = engine.CreateModule<OverworldGameModule>();

    engine.Play();

    engine.Shutdown();

    return 0;
}