#include "Game.h"
#include <cstdio>

bool Game::Initialize()
{
    if (!resources_.Load())
    {
        std::fprintf(stderr, "%s\n", resources_.Error().c_str());
        MessageBoxA(g2_GetHwnd(), resources_.Error().c_str(), "Resource error",
                    MB_OK | MB_ICONERROR);
        return false;
    }
    if (!renderer_.Initialize())
    {
        return false;
    }
    Reset();
    time_.Reset();
    resources_.PlayStart();
    return true;
}

void Game::Shutdown()
{
    resources_.Release();
}

void Game::Reset()
{
    player_.Reset();
    zombies_.Reset();
    state_.Reset();
}

int Game::Update()
{
    time_.Update();
    if (GetForegroundWindow() != g2_GetHwnd())
    {
        return 0;
    }
    input_.Update();
    if (input_.Pressed(VK_ESCAPE))
    {
        state_.TogglePause();
        return 0;
    }
    if (state_.IsPaused())
    {
        return 0;
    }
    if (input_.Pressed('R'))
    {
        Reset();
        return 0;
    }
    player_.Update(time_.DeltaTime(), input_.Movement(), input_.Mouse(), bounds_);
    zombies_.Update(time_.DeltaTime(), player_.Position());
    return 0;
}

int Game::Render() const
{
    renderer_.Render(resources_, player_, zombies_, state_, input_.Mouse());
    return 0;
}
