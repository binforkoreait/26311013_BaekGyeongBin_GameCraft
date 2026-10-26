#include "GameInput.h"
#include <glc2d.h>

void GameInput::Update()
{
    mouse_ = {float(g2_GetMouseX()), float(g2_GetMouseY())};
}

bool GameInput::Pressed(int key) const
{
    return g2_GetKeyboard()[key] == EINPUT_DOWN;
}

bool GameInput::Held(int key) const
{
    const int state = g2_GetKeyboard()[key];
    return state == EINPUT_DOWN || state == EINPUT_PRESS;
}

Vec2 GameInput::Movement() const
{
    return {float(Held('D')) - float(Held('A')), float(Held('S')) - float(Held('W'))};
}

Vec2 GameInput::Mouse() const
{
    return mouse_;
}
