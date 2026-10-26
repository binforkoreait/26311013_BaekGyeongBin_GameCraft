#pragma once
#include "Math2D.h"
#include "SpriteAnimation.h"
enum class ZombieType
{
    Normal,
    Fast,
    Heavy
};

class Zombie
{
public:
    Zombie(ZombieType type, Vec2 position) : type_(type), position_(position)
    {
    }

    void Update(float dt, Vec2 target);
    float Speed() const;

    Vec2 Position() const
    {
        return position_;
    }

    int Frame() const
    {
        return animation_.Frame();
    }

    int SpriteRow() const
    {
        return 1 + static_cast<int>(type_);
    }

    bool FacingLeft() const
    {
        return facingLeft_;
    }

private:
    ZombieType type_;
    Vec2 position_;
    SpriteAnimation animation_;
    bool facingLeft_ = false;
};
