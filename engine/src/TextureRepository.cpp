#include "TextureRepository.h"

#include <string>
#include <string.h>
#include "ATexture.h"

TextureRepository::TextureRepository()
{
    LogTrace("TextureRepository::TextureRepository");

    TextureList = new std::map<const char*, ATexture*>();

}

TextureRepository::~TextureRepository()
{
    LogTrace("TextureRepository::~TextureRepository");

    delete(TextureList);
}

ATexture* TextureRepository::FindTexture(const char* filepath)
{
    auto begin = TextureList->begin();
    auto end = TextureList->end();
    while (begin != end)
    {
        auto element = *begin;

        if (strcmp(filepath, element.first) == 0)
        {
            return element.second;
        }

        begin++;
    }

    return NULL;
}

void TextureRepository::CacheTexture(ATexture* tex)
{
    std::pair<const char*, ATexture*> element;
    element.first = tex->GetTexturePath();
    element.second = tex;

    this->TextureList->insert(element);
}

void TextureRepository::EmptyCache()
{
    this->TextureList->clear();
}
