#pragma once
#include "GameInput.h"
#include "GameTime.h"
#include "GameStateController.h"
#include "GameRenderer.h"

class Game
{
public:
    bool Initialize();
    void Shutdown();
    int Update();
    int Render() const;

private:
    void Reset();
    ResourceManager resources_;
    Player player_;
    ZombieManager zombies_;
    GameInput input_;
    GameTime time_;
    GameStateController state_;
    GameRenderer renderer_;
    Bounds bounds_;
    int health_ = 5;
    float damageCooldown_ = 0, survival_ = 0;
};
