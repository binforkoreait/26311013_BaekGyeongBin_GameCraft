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
    health_ = 5;
    damageCooldown_ = survival_ = 0;
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
    if (input_.Pressed('R')) { Reset(); return 0; }
    if (health_ <= 0) { return 0; }
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
    survival_ += time_.DeltaTime();
    damageCooldown_ = std::max(0.0f, damageCooldown_ - time_.DeltaTime());
    for (const auto& zombie : zombies_.Zombies())
    {
        if (damageCooldown_ <= 0 && (zombie.Position() - player_.Position()).Length() < 34.0f)
        {
            --health_;
            damageCooldown_ = 1.0f;
            resources_.PlayHit();
            break;
        }
    }
    return 0;
}

int Game::Render() const
{
    renderer_.Render(resources_, player_, zombies_, state_, input_.Mouse(), health_, survival_);
    return 0;
}
