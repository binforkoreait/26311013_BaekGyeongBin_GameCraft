#pragma once
#include "Math2D.h"
#include "SpriteAnimation.h"

class Player
{
public:
    void Reset();
    void Update(float dt, Vec2 input, Vec2 aim, const Bounds& bounds);

    Vec2 Position() const
    {
        return position_;
    }

    int Frame() const
    {
        return animation_.Frame();
    }

    bool FacingLeft() const
    {
        return facingLeft_;
    }

private:
    Vec2 position_{640, 360};
    SpriteAnimation animation_;
    bool facingLeft_ = false;
};
