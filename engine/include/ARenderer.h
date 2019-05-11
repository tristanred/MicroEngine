#pragma once

#include "core.h"

#include <libtech/geometry.h>
#include "ARenderable.h"
#include <libtech/arraylist.h>

class ARenderable;
class ATexture;
class ConfigFile;
class FileCache;
class Viewport;
class Asset;
class ResourceManager;
class SpriteAnimation;

/**
 * \brief Parameters given to the renderer.
 */
struct RendererParameters
{
    char window_title[256];
    int window_width;
    int window_height;

    float renderScaleX;
    float renderScaleY;
};

/**
 * \brief Options that can be given to ARenderer::DrawTexture
 */
struct TextureDrawOptions
{
    enum POSITION_SYSTEM PosSystem;
};

/**
 * \brief Abstract renderer base class. This is handling all matters of graphics
 * and rendering.
 *
 * The ARenderer is meant to be the sole source of texture data. This class is
 * subclassed by a specific instance of a renderer (such as SDL or DirectX).
 * This allows a driver specific handling of the texture data.
 *
 * The renderer has various members to help with managing resources.
 * The FileCache is an intermediate layer with the Filesystem. Data that is read
 * from the disk is saved in the FileCache to avoid loading the same file many
 * times. If a file's contents is found, it will be copied from the memory
 * instead.
 *
 * The ARenderer also uses the ResourceManager that can be used by other
 * components to find needed assets.
 *
 * \remark The ARenderer does NOT own the FileCache or the ResManager, these
 * objects are created by the GameEngine and given to this class.
 *
 * \see SDLRenderer - One of the subclasses of SDLRenderer.
 * \see FileCache
 * \see ResourceManager
 */
class ENGINE_CLASS ARenderer
{
public:
    ARenderer();
    virtual ~ARenderer();

    FileCache* Cache; // Set externally, may be NULL if no cache is enabled
    ResourceManager* Resman;
    Viewport* RenderViewport;

    // Methods to be managed by the concrete class

    /**
     * \brief Initialize the engine with the default configuration.
     *
     * \return - True if the init suceeded.
     */
    virtual bool Initialize() = 0;

    /**
     * \brief Initialize the engine with the properties found in the config
     * file.
     *
     * \param config - Config file object to read from.
     *
     * \return - True if the init suceeded.
     */
    virtual bool Initialize(ConfigFile* config) = 0;

    /**
     * \brief Initialize the engine with the property object.
     *
     * \param params - Config object
     *
     * \return - True if the init suceeded.
     */
    virtual bool Initialize(RendererParameters* params) = 0;

    /**
     * \brief Draw an ARenderable to the renderer.
     *
     * If the ARenderable has children, it will draw itself first and then
     * draw its children on top.
     *
     * \param sprite - The renderable object to draw.
     */
    virtual void Draw(ARenderable* sprite) = 0;

    /**
     * \brief Draw a texture directly to the screen.
     *
     * Since textures do not have
     * position parameters, we need to provide X and Y manually.
     *
     * \param tex - Texture to draw
     * \param posX - Position X to draw the texture to.
     * \param posY - Position Y to draw the texture to.
     */
    virtual void DrawTexture(ATexture* tex, float posX, float posY) = 0;

    /**
     * \brief Draw a texture directly to the screen with parameters.
     *
     * Since textures do not have position parameters, we need to provide X
     * and Y manually.
     *
     * \param tex - Texture to draw
     * \param posX - Position X to draw the texture to.
     * \param posY - Position Y to draw the texture to.
     * \param opt - Options for the draw.
     */
    virtual void DrawTexture(ATexture* tex, float posX, float posY, struct TextureDrawOptions* opt) = 0;

    /**
     * \brief Create an empty texture.
     *
     * The ATexture instance that is returned is under the specific type
     * supported by the current renderer.
     *
     * \return ATexture
     */
    virtual ATexture* CreateTexture() = 0;

    /**
     * \brief Create a texture from a texture name.
     *
     * The texture name can be an identifier or a file path.
     *
     * Usually this methods checks in the ResourceManager to see if the asset
     * can be located. If it is not, it will load the file and call the
     * ARenderer::CreateTexture(Asset*) overload to create the texture.
     *
     * \param textureName - Name of the texture to load.
     *
     * \return ATexture
     */
    virtual ATexture* CreateTexture(const char* textureName);

    /**
     * \brief Create a texture from an Asset class.
     *
     * Given an asset with some data, this creates a texture from the binary of
     * the asset. Currently this is not checking if the Asset is an image type
     * before trying to create a texture from it.
     *
     * \param asset - Asset object with the content to create a texture from.
     *
     * \return ATexture
     */
    virtual ATexture* CreateTexture(Asset* asset);

    /**
     * \brief Create a texture from binary data.
     *
     * Take some bytes and create a texture from it. This highly depends on the
     * renderer being used.
     *
     * \param data - Binary content of the teture.
     * \param length - How many bytes of content
     *
     * \return ATexture
     */
    virtual ATexture* CreateTexture(void* data, int length) = 0;

    /**
     * \brief Delete a texture.
     *
     * This should free the contents of the texture but not the Asset that owns
     * the bytes since the Asset owns the data.
     *
     * \param texture - Texture to delete.
     */
    virtual void DeleteTexture(ATexture* texture) = 0;

    /**
     * \brief Get the size of the window of the game.
     *
     * \return FSize - Size of the window in pixels.
     */
    virtual FSize GetWindowSize() = 0;

    /**
     * \brief Start the draw phase.
     *
     * In some renderer's cases, we need to call a START and END draw functions
     * this can initialize the resources for the frame draw.
     */
    virtual void BeginDraw() = 0;

    /**
     * \brief End the draw phase.
     *
     * In some renderer's cases, we need to call a START and END draw functions
     * this can initialize the resources for the frame draw.
     */
    virtual void EndDraw() = 0;

    /**
     * \brief De-initializes the renderer and release all resources associated
     * with it.
     */
    virtual void Shutdown() = 0;

    // Utility methods provided by the base ARenderer class

    /**
     * \brief Load a list of files and add those as textures in a Texture Array.
     *
     * \param fileNames - List of file paths.
     * \param length - Amount of entries in the 'fileNames' list.
     *
     * \return ArrayList<ATexture> - Returns list of textures createds
     */
    ArrayList<ATexture*>* CreateTextureList(const char* fileNames[], int length);

    /**
     * \brief Load frames from a file path. Executes multiple strategies to
     * extract frames in the correct way. See FrameListLoader for the
     * implementation.
     *
     * \param path - Path of the frames to load.
     *
     * \return ArrayList<ATexture> - Returns list of textures createds
     */
    ArrayList<ATexture*>* LoadFrames(const char* path);

    /**
     * \brief Convert a Sprite Animation into a texture strip.
     *
     * \param anim - Animation to convert
     */
    ATexture* MakeTextureFromAnimation(SpriteAnimation* anim);

    /**
     * \brief Set a flag to save the next frame to an image file.
     */
    virtual void ScreenshotNextFrame() = 0;

    /**
     * \brief Save a renderable object and its children hierarchy to an
     * image file.
     *
     * \param object - Renderable to save.
     * \param path - File path for the output.
     */
    virtual void SaveToFile(ARenderable* object, const char* path) = 0;
};
