#include <stdio.h>

#include <GameEngine.h>

int main(int argc, char** argv)
{
    printf("Hello RPG.");

    GameEngine engine;
    engine.Initialize();

    engine.Play();

    engine.Shutdown();

    return 0;
}