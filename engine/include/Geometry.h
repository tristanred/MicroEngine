#pragma once

struct FPosition
{
    float X;
    float Y;

    FPosition()
    {
        X = 0;
        Y = 0;
    }

    FPosition(float x, float y)
    {
        X = x;
        Y = y;
    }
};

struct FSize
{
    float Width;
    float Height;

    FSize()
    {
        Width = 0;
        Height = 0;
    }

    FSize(float w, float h)
    {
        Width = w;
        Height = h;
    }
};