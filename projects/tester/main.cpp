#include <GameEngine.h>
#include <GameModule.h>
#include <Rendering/AFont.h>
#include <Rendering/ASprite.h>
#include <Rendering/AText.h>
#include <libtech/arraylist.h>
#include <libtech/filecache.h>
#include <libtech/fsutils.h>
#include <stdio.h>
#include <string.h>

#include <list>

#include "Events/Event.h"
#include "FormatLoaders/TPXmlReader.h"
#include "GameTestModule.h"
#include "TextureTestModule.h"
#include "core.h"
#include "libtech/pathutils.h"
#include "libtech/sysutils.h"

int main(int argc, char** argv)
{
    Event<int>* x = new Event<int>();

    GameEngine* eng = new GameEngine();
    eng->Initialize();

    GameModule* mod = eng->ActivateModule<GameTestModule>();
    (void)mod;

    eng->Play();

    return 0;
}
