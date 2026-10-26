#pragma once

class GameStateController
{
public:
    void Reset();
    void TogglePause();
    bool IsPaused() const;

private:
    bool paused_ = false;
};
