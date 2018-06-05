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

int main(int argc, char** argv)
{
    GameEngine* eng = new GameEngine();
    eng->Initialize();

    GameModule* mod = eng->CreateModule<GameTestModule>();

    //ASprite* x = mod->CreateSprite();

    //AFont* txtFont = mod->CreateFont();
    //txtFont->LoadFontFile("assets/engine/arial.ttf");
    //
    //AText* txt = mod->CreateText();
    //txt->SetFont(txtFont);
    //txt->SetText("Hello texts");
    //txt->SetPosition(FPosition(150.0, 50.0));
    //txt->SetColor(0xFF000000);

    //ATexture* tex = eng->TextureRepo->LoadFromFile("assets/engine/test_asset.png");
    //x->SetTexture(tex);
    
    eng->Play();

    return 0;

    char* data1 = new char[6];
    char* data2 = new char[6];

    strcpy(data1, "abcde");
    strcpy(data2, "qwert");

    write_characters("one.txt", data1, 5);
    write_characters("two.txt", data2, 5);

    FileCache c;

    size_t l1 = 0;
    uint8_t* dat1 = c.ReadFileContents("one.txt", &l1);
    dat1[l1] = '\0';

    size_t l2 = 0;
    uint8_t* dat2 = c.ReadFileContents("one.txt", &l2);
    dat2[l2] = '\0';

    size_t l3 = 0;
    uint8_t* dat3 = c.ReadFileContents("two.txt", &l3);
    dat3[l3] = '\0';

    printf("Data 1 Size = %zd\n", l1);
    printf("Data 1 = %s\n", dat1);

    printf("Data 2 Size = %zd\n", l2);
    printf("Data 2 = %s\n", dat2);

    printf("Data 3 Size = %zd\n", l3);
    printf("Data 3 = %s\n", dat3);


    char buf[256];
    scanf("%s", buf);

    return 0;
}