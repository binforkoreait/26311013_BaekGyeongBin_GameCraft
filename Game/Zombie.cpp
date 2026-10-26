#include "Zombie.h"

float Zombie::Speed() const
{
    switch (type_)
    {
    case ZombieType::Fast:
        return 140;
    case ZombieType::Heavy:
        return 55;
    default:
        return 80;
    }
}

void Zombie::Update(float dt, Vec2 target)
{
    const Vec2 offset = target - position_;
    // Week 2 movement preview: stop near the player, without damage.
    const float step = std::min(Speed() * dt, std::max(0.0f, offset.Length() - 48));
    position_ = position_ + offset.Normalized() * step;
    if (std::abs(offset.x) > 1)
    {
        facingLeft_ = offset.x < 0;
    }
    animation_.Update(dt, step > 0.001f);
}
