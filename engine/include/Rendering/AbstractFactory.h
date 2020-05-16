#pragma once

#include "core.h"

class GameEngine;
class RenderableObject;
class ARenderer;
class ASprite;
class AText;
class AFont;
class ATexture;
class APlatform;

class AMouse;
class AKeyboard;

/**
 * \brief List of graphic renderers that are implemented.
 *
 * \remark At the moment, only SDL is implemented. Despite what the
 * inclusion of the RENDERER_DIRECTX value, DirectX is NOT implemented yet,
 * it is only to test multiple values in the enum.
 */
enum ImplementedRenderers
{
    RENDERER_SDL,
    RENDERER_DIRECTX,
    RENDERER_NULL
};

/**
 * \brief Abstract factory in charge of handing out platform specific instances.
 *
 * The Abstract factory is used to generate concrete type implementations
 * depending on the current renderer. This class is at the core of the
 * Abstract Graphic Layer system. Everytime a class from the outside need to
 * create a sprite or a texture, it must ask the AbstractFactory for it.
 *
 * From within a specific library, there is no need to go through this factory.
 * For example, from a SDLText we can create a new SDLTexture manually
 * because we know that SDL is the current renderer anyway.
 *
 * The way to detect which renderer is a mix of #define depending on the
 * platform and a list of implemented renderers. Since SDL is the only
 * implemented renderer the checking isn't really correct.
 */
class ENGINE_CLASS AbstractFactory
{
public:
    AbstractFactory();
    ~AbstractFactory();

    static enum ImplementedRenderers ActivatedRenderer;

    /**
     * \brief Create a platform specific ARenderer instance.
     *
     * \see SDLRenderer
     * \return ARenderer
     */
    static ARenderer* CreateRenderer();

    /**
     * \brief Create a platform specific AText instance.
     *
     * \param renderer - Owning ARenderer instance
     * \see SDLText
     * \return AText
     */
    static AText* CreateText(GameEngine* engine);

    /**
     * \brief Create a platform specific ATexture instance.
     *
     * \param renderer - Owning ARenderer instance
     * \see SDLTexture
     * \return ATexture
     */
    static ATexture* CreateTexture(GameEngine* engine);

    /**
     * \brief Create a platform specific AMouse instance.
     *
     * \see SDLMouse
     * \return AMouse
     */
    static AMouse* CreateMouse();

    /**
     * \brief Create a platform specific AKeyboard instance.
     *
     * \see SDLKeyboard
     * \return AKeyboard
     */
    static AKeyboard* CreateKeyboard();

    /**
     * \brief Create a platform specific AFont instance.
     *
     * \see SDLFont
     * \return AFont
     */
    static AFont* CreateTextFont(GameEngine* engine);

    /**
     * \brief Create a platform specific event handler.
     *
     * \see SDLPlatform
     * \return APlatform
     */
    static APlatform* CreatePlatformHandler(GameEngine* engine);
};