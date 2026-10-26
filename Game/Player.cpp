#include "Player.h"

void Player::Reset()
{
    position_ = {640, 360};
    facingLeft_ = false;
    animation_.Reset();
}

void Player::Update(float dt, Vec2 input, Vec2 aim, const Bounds& bounds)
{
    const Vec2 previous = position_;
    position_ = bounds.Clamp(position_ + input.Normalized() * (240.0f * dt));
    if (std::abs(aim.x - position_.x) > 1)
    {
        facingLeft_ = aim.x < position_.x;
    }
    animation_.Update(dt, (position_ - previous).Length() > 0.001f);
}
