#pragma once

enum GameMouseState
{
    MOUSE_UP,
    MOUSE_DOWN
};

class GameMouseEvent
{
    int positionX;
    int positionY;
    GameMouseState state;
};

class GameKeyboardEvent
{

};