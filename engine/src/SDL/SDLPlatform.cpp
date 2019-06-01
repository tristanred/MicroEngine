#ifdef SUPPORT_SDL

#include "SDL/SDLPlatform.h"

#include "SDL.h"
#include "ARenderer.h"

SDLPlatform::SDLPlatform(ARenderer* renderer) : APlatform(renderer)
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