#ifdef SUPPORT_SDL

#include "Rendering/SDL/SDLPlatform.h"

#include "SDL.h"
#include "GameEngine.h"

SDLPlatform::SDLPlatform(GameEngine* engine) : APlatform(engine)
{

}

SDLPlatform::~SDLPlatform()
{
}

void SDLPlatform::HandleEvents()
{
    SDL_Event myEvent;
    while (SDL_PollEvent(&myEvent)) {
        switch (myEvent.type)
        {
        case SDL_QUIT:
        {
            this->RequestExit = true;

            break;
        }
        case SDL_WINDOWEVENT:
        {
            break;
        }
        default:
            break;
        }
    }
}

void SDLPlatform::Shutdown()
{
}
#endif