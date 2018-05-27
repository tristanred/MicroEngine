#include "test.h"

class GameEngine;
class AModule;
class ASprite;

#include "GameEngine.h"
#include "GameModule.h"

#include <SDL.h>

struct MyData
{
    int a;
    int b;
    int c;
};

void do_stuff()
{
    auto x = new GameEngine();

    auto y = x->CreateModule<GameModule>();

    // Create the game engine
    GameEngine* engine = new GameEngine();
    
    // Build a module
    GameModule* mod = engine->CreateModule<GameModule>();
    //
    //// Create and attach a sprite #1
    //ASprite* sprite = engine->CreateSprite();
    //mod->Attach(sprite);
    //
    //// Create and attach a sprite #2
    //ASprite* sprite = mod->CreateSprite();
    //
    //// Start the engine
    //engine->Start();
    //
    //// Game Loop #1 Take control and loop
    //engine->Play();
    //
    //// Game Loop #2 Play frames 
    //while(true)
    //{
    //    engine->PlayOne();
    //}
    //
    //// Game Loop #3 Play frames without FPS lock
    //while(true)
    //{
    //    engine->PlayOneUnlocked();
    //}
    //
    //// Close everything
    //engine->Shutdown();
}
