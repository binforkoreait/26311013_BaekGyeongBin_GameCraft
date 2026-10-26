#pragma once
#include "Math2D.h"

class GameInput
{
public:
    void Update();
    bool Pressed(int key) const;
    bool Held(int key) const;
    Vec2 Movement() const;
    Vec2 Mouse() const;

private:
    Vec2 mouse_{640, 360};
};
