#include "core.h"

#include <stdio.h>
#include <string.h>

#include <libtech/filecache.h>
#include <libtech/fsutils.h>

#include <GameEngine.h>
#include <GameModule.h>
#include <Rendering/ASprite.h>
#include <Rendering/AText.h>
#include <Rendering/AFont.h>
#include <ConfigFile.h>

#include "GameTestModule.h"

#include "libtech/pathutils.h"
#include "libtech/sysutils.h"

#include <list>

#include <libtech/fsutils.h>
#include <libtech/arraylist.h>
#include "FormatLoaders/TPXmlReader.h"

#include "Events/Event.h"

int main(int argc, char** argv)
{
    Event<int>* x = new Event<int>();

    GameEngine* eng = new GameEngine();
    eng->Initialize();

    GameModule* mod = eng->CreateModule<GameTestModule>();
    (void)mod;

    eng->Play();

    return 0;
}
