#pragma once

class GameEngine;
class RenderableObject;
class ASprite;
class AText;
class AFont;
class ATexture;
class ARenderer;
class Viewport;

class TickTimer;

#include <list>
#include <stdint.h>

#include "GameEngine.h"
#include "core.h"
#include "Controls/CBaseControl.h"
#include "Controls/CButton.h"
#include "Controls/CLabel.h"

enum GameModuleState
{
    UNINITIALIZED,  // Object is not created in memory
    LOADED,         // Object in memory, module is dormant.
    ACTIVATED       // Module is running, receives Update/Draw calls
};

/**
 * \brief Modular separation of a piece of game content.
 *
 * The GameModule class is meant to be a segment of a game, such as an Overworld
 * screen, an inventory screen, maybe a loading screen, etc.
 *
 * GameModules should be subclassed in order to include their own
 * module specific functionalities.
 *
 * Modules "own" the sprites and drawable game elements. This allows
 * loading/unloading of parts of the game if they are not used. Multiple
 * dungeons of a game could be modules for example.
 *
 * A GameModule also provides wrapper methods to create game objects like
 * sprites, texts and other stuff. This is to avoid reaching into a deep
 * hierarchy in order to hit the game engine to create objects. The wrapper
 * methods can also introduce some utility methods such as
 * GameModule::CreateText(AFont*).
 *
 * /remark GameModule is still very much a work in progress, I'm still
 * assessing the level of functionality that I want them to be responsible for.
 */
class ENGINE_CLASS GameModule
{
public:
    explicit GameModule(GameEngine* engine);
    virtual ~GameModule();

    std::list<RenderableObject*>* Objects;



    GameModuleState ModuleState = UNINITIALIZED;

    virtual void Load();

    virtual void Activate();

    virtual void Unload();

    virtual void Stop();



    /**
     * \brief Get a pointer to the game's renderer.
     *
     * \return ARenderer
     */
    ARenderer* GetRenderer();

    /**
     * \brief Get a pointer to the game's Engine class.
     *
     * \return GameEngine
     */
    GameEngine* GetEngine();

    /**
     * \brief Create a Sprite object and attaches it to this Module's
     * object-list.
     *
     * \return ASprite
     */
    template <typename TSubType = ASprite>
    TSubType* CreateSprite();

    /**
     * \brief Create a Sprite object with a texture and attaches it to this
     * Module's object-list.
     *
     * \param texture - Texture to initially apply.
     *
     * \return ASprite
     */
    template <typename TSubType = ASprite>
    TSubType* CreateSprite(ATexture* texture);

    /**
     * \brief Create a Text object and attaches it to this Module's object-list.
     *
     * \return AText
     */
    AText* CreateText();

    /**
     * \brief Create a Text object with a font and attaches it to this
     * Module's object-list.
     *
     * \param textFont - Font to initially apply.
     *
     * \return AText
     */
    AText* CreateText(AFont* textFont);

    /**
     * \brief Create a Font objet.
     *
     * \return AFont
     */
    AFont* CreateTextFont();

    /**
     * \brief Create a blank texture.
     *
     * \return ATexture
     */
    ATexture* CreateTexture();

    /**
     * \brief Create a texture from the provided resource name.
     *
     * \param textureName - Name of the texture to load. Can be a file path
     * or a friendly name given in the ResourceManager.
     *
     * \return ATexture
     */
    ATexture* CreateTexture(const char* textureName);


    /**
     * \brief Frees an object.
     *
     * \param object - Object to free.
     */
    void DestroyObject(RenderableObject* object);


    /**
     * \brief Create a viewport to use. If no viewports exist, the first one
     * will be used automatically.
     *
     * \return Viewport
     */
    virtual Viewport* CreateViewport();

    /**
     * \brief Add an object to be drawn
     *
     * That object should have been created manually because using
     * CreateSprite/CreateText methods already add the new object
     * to the list.
     *
     * \remark Will probably be reworked because the Create* methods should
     * maybe not add automatically into the container.
     */
    virtual void AttachRenderable(RenderableObject* object);


    /**
     * \brief Process the Update loop of the GameModule.
     *
     * \param deltaTime - Time difference between this update and the last, in
     * miliseconds.
     */
    virtual void Update(unsigned int deltaTime);

    /**
     * \brief Draw the GameModule's elements.
     *
     * \param renderer - Renderer instance to use.
     */
    virtual void Draw(ARenderer* renderer);

    // Helper objects management
    std::list<TickTimer*>* Timers;

    /**
     * \brief Create a stopped timer.
     *
     * This timer will already be linked to the Module so it's update will be
     * called automatically.
     *
     * \param totalTime - Time to run in miliseconds.
     *
     * \return TickTimer - Timer instance.
     */
    virtual TickTimer* CreateTimer(uint32_t totalTime);

    /**
     * \brief Destroy a timer instance.
     *
     * \param timer - Timer instance to delete
     */
    virtual void DestroyTimer(TickTimer* timer);

protected:
    bool moduleEnabled;

    /**
     * \brief Create a Control element of a base class. Type T should be
     * inheriting from CBaseControl.
     *
     * \return T - Created control.
     */
    template<class T>
    T* CreateControl();

private:
    GameEngine* Engine;

    /**
     * \brief Update all timers linked to this game module.
     *
     * \param deltaTime - Time difference between this update and the last, in
     * miliseconds.
     */
    void UpdateTimers(uint32_t deltaTime);
};

template<>
inline CButton* GameModule::CreateControl<CButton>()
{
    CButton* newbutan = new CButton(this->Engine);
    return newbutan;
}

template<>
inline CLabel* GameModule::CreateControl<CLabel>()
{
    CLabel* newlab = new CLabel(this->Engine);
    return newlab;
}

template<typename TSubType>
TSubType* GameModule::CreateSprite()
{
    LogTrace("GameModule::CreateSprite");

    TSubType* x = this->Engine->CreateSprite<TSubType>();

    this->AttachRenderable(x);

    return x;
}

template<typename TSubType>
TSubType* GameModule::CreateSprite(ATexture* texture)
{
    LogTrace("GameModule::CreateSprite");

    TSubType* x = this->Engine->CreateSprite<TSubType>();
    x->SetTexture(texture);

    this->AttachRenderable(x);

    return x;
}
