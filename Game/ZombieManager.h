#pragma once
#include "Zombie.h"
#include <vector>

class ZombieManager
{
public:
    void Reset();
    void Update(float deltaTime, Vec2 target);
    const std::vector<Zombie>& Zombies() const;

private:
    std::vector<Zombie> zombies_;
};
