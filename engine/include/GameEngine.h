#pragma once

class ASprite;
class ATexture;
class AText;
class AFont;
class FileLogger;
class FileCache;
class APlatform;
class AMouse;
class AKeyboard;
class Viewport;
class DebugLayer;
class ResourceManager;
class GameModule;

#include <list>
#include <cstdint>
using namespace std;

#include "core.h"
#include "ARenderer.h"
#include <libtech/geometry.h>

/**
 * \brief Core engine class
 *
 * This class is the main class of the library. Its purpose is to store the
 * game modules and provide services to the consumers of the library
 */
class ENGINE_CLASS GameEngine
{
public:
    std::list<GameModule*>* Modules;

    // Game Services
    ARenderer* Renderer;
    FileLogger* GameLog;
    FileCache* FilesCache;
    ResourceManager* ResManager;

    int wantedFPS;
    long int previousFrameTime;
    long int currentFrameTime;

    // Engine State
    bool InitializationComplete;

    // Input devices
    AMouse* Mouse;
    AKeyboard* Keyboard;

    // Platform manager
    APlatform* Platform;

    // Debugging
    DebugLayer* debugLayer;

    GameEngine();
    ~GameEngine();

    /**
     * \brief Startup function of the engine. Needs to be called before other
     * engine methods are called.
     *
     * This function creates the structures used by the engine, it handles
     * creating the abstract renderer and opening the initial window.
     *
     * The engine can be configured with the config file located at
     * assets/engine/engine_config.xml.
     */
    void Initialize();

    /**
     * \brief Shutdown procedure of the engine.
     *
     * This is closing the windows, freeing resources and getting
     * ready for disposing the engine instance.
     *
     * This function should be called before the class destructor is
     * called.
     *
     * \remark This function is mostly unimplemented at the moment. Since we only
     * have a single instance of GameEngine and it dies at the end of the
     * execution, I just avoid calling the method.
     */
    void Shutdown();

    /**
     * \brief Starts looping infinitely in the engine.
     *
     * This is one of the 3 looping functions of the engine. This function
     * starts an infinite loop and executes the update/draw loop when the time
     * to process a frame is reached.
     *
     * This function will return if the ESCAPE key is pressed. Used to quit the
     * game.
     */
    void Play();

    /**
     * \brief Executes 1 frame of the engine if the time for a frame is reached.
     *
     * This is the second of the 3 looping functions. This function executes a
     * single pass of the update/draw loop. It will also check if the necessary
     * time has passed to process a new frame under the wanted FPS so it safe
     * to call inside a repeat loop.
     */
    void PlayOne();

    /**
     * \brief Executes 1 frame of the engine ignoring the FPS limit.
     *
     * This is the third of the 3 looping functions. This function executes a
     * single pass of the update/draw loop. It will NOT check if the necessary
     * time has passed to process a frame so calling this function repeatedly
     * will draw frames continuously.
     */
    void PlayOneUnlocked();

    /**
     * \brief Get the time between the last frame and the current frame, in
     * miliseconds.
     */
    long GetDeltaTime();

    /**
     * \brief Create a GameModule instance. You must provide a generic type
     * that inherits from GameModule.
     *
     * This is used to create instances of your GameModules, if you create a
     * class derived from GameModule you must use this method to create
     * instances of the module. This attaches the game module to the game
     * engine's context.
     *
     * \return A linked instance of the GameModule subclass.
     */
    template <typename TModule = GameModule>
    TModule* CreateModule();

    /**
     * \brief Create an ASprite instance.
     *
     * This creates an instance of ASprite with the proper inner type for
     * the current rendering library.
     *
     * \see SDLSprite
     *
     * \return ASprite.
     */
    template <typename TSubType = ASprite>
    TSubType* CreateSprite();

    /**
     * \brief Create an AText instance.
     *
     * This creates an instance of AText with the proper inner type for the
     * current rendering library.
     *
     * \see SDLText
     *
     * \return AText
     */
    AText* CreateText();

    /**
     * \brief Create an AFont instance.
     *
     * This creates an instance of AFont with the proper inner type for the
     * current rendering library.
     *
     * \see SDLFont
     *
     * \return AFont
     */
    AFont* CreateTextFont();

    /**
     * \brief Create an empty ATexture instance.
     *
     * This creates an empty instance of ATexture with the proper inner type for
     * the current rendering library.
     *
     * \see SDLTexture
     *
     * \return ATexture
     */
    ATexture* CreateTexture();

    /**
     * \brief Create an ATexture from a texture name.
     *
     * This creates an instance of ATexture by name. The name can be a file
     * path or an identifier previously given in ResourceManager::AddFile.
     *
     * \param textureName - The path or identifier of the texture to use.
     *
     * \see SDLTexture
     *
     * \return ATexture
     */
    ATexture* CreateTexture(const char* textureName);

    /**
     * \brief Release a ATexture created by the CreateTexture methods.
     * This should be called instead of the destructor of the object.
     *
     * Only the engine should be in charge of destroying engine objects.
     *
     * \param textureObject - The texture to destroy.
     */
    void ReleaseObject(ATexture* textureObject);

    /**
     * \brief Relase an ARenderable object created by the Create- methods.
     * This should be called instead of the destructor of the object.
     *
     * Only the engine should be in charge of destroying engine objects.
     *
     * \param renderableObject - The object to destroy.
     */
    void ReleaseObject(ARenderable* renderableObject);

    /**
     * \brief Get the engine's default texture.
     *
     * The default texture is a singleton used to represent a dummy texture.
     *
     * \remark Right now, a new texture is created each time but the
     * implementation will be changed to re-use the same instance.
     *
     * \return ATexture - Dummy style texture.
     */
    ATexture* GetDefaultTexture();

    // -------------------- Viewport --------------------
    std::list<Viewport*>* GameViewports;

    /**
     * \brief Set the provided parameter as the active viewport.
     *
     * \param view - The viewport to activate.
     */
    void SelectViewport(Viewport* view);

    /**
     * \brief Create a new viewport activate it it is the first viewport.
     *
     * \return Viewport
     */
    Viewport* CreateViewport();

    /**
     * \brief Get the currently active viewport
     *
     * \return Viewport
     */
    Viewport* GetCurrentViewport();

    /**
     * \brief Return the mouse coordinates relative to the current viewport.
     *
     * \return FPosition
     */
    FPosition GetMouseRelativePosition();

    /**
     * \brief Show the debug layer.
     *
     * The debug layer is a topmost layer that can be filled with information
     * about the running engine instance.
     *
     * \see DebugLayer
     */
    void ShowDebugLayer();

    /**
     * \brief Hide the debug layer.
     *
     * \see DebugLayer
     */
    void HideDebugLayer();

private:

    /**
     * \brief Update loop for the engine.
     *
     * \param deltaTime - Time in miliseconds since the previous update.
     */
    void Update(unsigned int deltaTime);

    /**
     * \brief Entrypoint into the Draw method for each module
     */
    void DrawModules();

    /**
     * \brief Checks if enough time has passed since the last frame to draw
     * a new frame at the wanted FPS.
     *
     * \return - True if it time to draw a new frame.
     */
    bool TimeForNextFrame();
};

/**
 * \brief Implementation of the CreateModule function
 */
template<typename TModule>
TModule* GameEngine::CreateModule()
{
    TModule* newModule = new TModule(this);
    this->Modules->push_back(newModule);

    return newModule;
}

template<typename TSubType>
TSubType* GameEngine::CreateSprite()
{
    LogTrace("GameEngine::CreateSprite");

    return new TSubType(Renderer);
}
