#pragma once

class GameEngine;
class ATexture;
class AMouse;
class AKeyboard;

#include "core.h"
#include "CBaseControl.h"

/**
 * Clickable button class. Has many states and can show a different texture 
 * based on the state. There is no need to introduce a texture for each state
 * and if no texture exists it will revert to the 'Enabled' texture. 
 *
 * Giving an 'enabled' texture is optional for click zones that are invisible.
 * It doesn't really make sense to have a null 'enabled' texture but valid
 * disabled/down/hover textures as the button will be invisible other than 
 * when the button is hovered for example.
 */
class ENGINE_CLASS CButton : public CBaseControl
{
public:
    enum Button_State
    {
        ENABLED,
        DISABLED,
        DOWN,
        HOVERED
    };

    Button_State CurrentState;

    CButton(GameEngine* engine);
    ~CButton();

    /**
     * Main Initializer for a button. Uses a Size for the object and a texture
     * for each button state.
     */
    void Initialize(FSize size, ATexture* enabledTexture = NULL, ATexture* disabledTexture = NULL, ATexture* downTexture = NULL, ATexture* overTexture = NULL);

    /**
     * Update the button state. Mostly checks for the mouse pointer to see if 
     * the button is clicked or hovered.
     */
    void Update() override;

    /**
     * Gets if the button is in an enabled state. 
     * If a button is enabled it will react to mouse clicks and mouse hovers.
     */
    bool IsEnabled();
    
    /**
     * Set the button enabled state.
     * If a button is enabled it will react to mouse clicks and mouse hovers.
     */
    void Enable(bool status);
    
    /**
     * Checks if the button is being clicked. 
     * To avoid repeating signals that a button is clicked on every frame that 
     * we call IsClicked we can use the parameter 'clickedLockButton' to only
     * report a click once. The button will have to be depressed and re-pressed
     * to return true again.
     * 
     * @param clickedLockButton 
     */
    bool IsClicked(bool clickedLockButton = false);

    ATexture* GetTexture() override;

private:
    /* Flag to check if the button response to the mouse clicks and hovers.
     * The button won't really update if it's disabled. Setting this flag to 
     * false will set the state to DISABLED too, opposite when going enabled.
     */
    bool isEnabled;

    /*
     * The lock is used to avoid repeats of the IsClicked result. If we press
     * down a button and leave the mouse down and if the caller keeps calling
     * IsClicked every frame, the button will stay clicked and keep going into
     * the check if clicked. The IsClicked check might only want to trigger
     * once on every click. Every time we go back from the DOWN state, we reset
     * the lock to false. As long as the lock is true, the IsClicked will not
     * return true.
     */
    bool clickLock;
    
    ATexture* enabledTexture;
    ATexture* disabledTexture;
    ATexture* downTexture;
    ATexture* mouseOverTexture;
};
