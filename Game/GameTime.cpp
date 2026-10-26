#include "GameTime.h"
#include <algorithm>

void GameTime::Reset()
{
    previous_ = std::chrono::steady_clock::now();
    deltaTime_ = 0;
}

void GameTime::Update()
{
    const auto current = std::chrono::steady_clock::now();
    deltaTime_ = std::clamp(std::chrono::duration<float>(current - previous_).count(), 0.0f, 0.05f);
    previous_ = current;
}

float GameTime::DeltaTime() const
{
    return deltaTime_;
}
