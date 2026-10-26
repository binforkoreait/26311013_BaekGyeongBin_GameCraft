#pragma once
#include "Player.h"
#include "ZombieManager.h"
#include "ResourceManager.h"
#include "GameStateController.h"

class GameRenderer
{
public:
    bool Initialize();
    void Render(const ResourceManager& resources, const Player& player,
                const ZombieManager& zombies, const GameStateController& state, Vec2 mouse) const;

private:
    int pauseFont_ = -1;
};
