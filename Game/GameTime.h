#pragma once
#include <chrono>

class GameTime
{
public:
    void Reset();
    void Update();
    float DeltaTime() const;

private:
    std::chrono::steady_clock::time_point previous_;
    float deltaTime_ = 0;
};
