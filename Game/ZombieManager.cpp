#include "ZombieManager.h"

void ZombieManager::Reset()
{
    zombies_.clear();
    zombies_.emplace_back(ZombieType::Normal, Vec2{180, 210});
    zombies_.emplace_back(ZombieType::Normal, Vec2{1080, 500});
    zombies_.emplace_back(ZombieType::Fast, Vec2{1080, 210});
    zombies_.emplace_back(ZombieType::Heavy, Vec2{180, 500});
}

void ZombieManager::Update(float deltaTime, Vec2 target)
{
    for (auto& zombie : zombies_)
    {
        zombie.Update(deltaTime, target);
    }
}

const std::vector<Zombie>& ZombieManager::Zombies() const
{
    return zombies_;
}
