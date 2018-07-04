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

int main(int argc, char** argv)
{
    const char* testPath = "E:\\Prog\\MicroEngine\\build\\Debug\\assets\\engine\\arial.ttf";
    char* testPath2 = new char[256];
    strcpy(testPath2, "E:\\Prog\\MicroEngine\\build\\Debug\\assets\\engine\\arial.ttf");


    replace_path_slashes(testPath2);
    char* res1 = get_file_name(testPath2);
    size_t count1 = strlen(res1);

    char* res2 = get_file_name_noext(testPath2);
    size_t count2 = strlen(res2);

    char* res3 = get_file_extension(testPath2);
    size_t count3 = strlen(res3);

    char* res4 = get_parent_directory_path(testPath2);
    size_t count4 = strlen(res4);

    auto partlist = get_path_parts(testPath2);
    auto partlistBegin = partlist->begin();
    auto partlistEnd = partlist->end();
    while (partlistBegin != partlistEnd)
    {
        auto partstr = *partlistBegin;

        printf(partstr);
        partlistBegin++;
    }
    
    GameEngine* eng = new GameEngine();
    eng->Initialize();

    GameModule* mod = eng->CreateModule<GameTestModule>();

    eng->Play();

    return 0;
}