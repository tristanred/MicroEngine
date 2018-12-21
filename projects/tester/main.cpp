#include "core.h"

#include <stdio.h>
#include <string.h>

#include <libtech/filecache.h>
#include <libtech/fsutils.h>

#include <GameEngine.h>
#include <GameModule.h>
#include <ASprite.h>
#include <AText.h>
#include <AFont.h>
#include <TextureRepository.h>
#include <ConfigFile.h>

#include "GameTestModule.h"

#include "libtech/pathutils.h"

#include <list>

#include <libtech/fsutils.h>
#include <libtech/arraylist.h>

int main(int argc, char** argv)
{
    GameEngine* eng = new GameEngine();
    eng->Initialize();

    GameModule* mod = eng->CreateModule<GameTestModule>();

    eng->Play();

    return 0;
}
