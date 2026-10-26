#pragma once
#include <cmath>

class SpriteAnimation
{
public:
    void Update(float dt, bool moving)
    {
        if (!moving)
        {
            Reset();
        }
        else
        {
            time_ = std::fmod(time_ + dt, 0.5f);
        }
    }

    void Reset()
    {
        time_ = 0;
    }

    int Frame() const
    {
        return static_cast<int>(time_ * 8) % 4;
    }

private:
    float time_ = 0;
};
