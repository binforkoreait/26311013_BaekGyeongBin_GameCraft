#include "GameStateController.h"

void GameStateController::Reset()
{
    paused_ = false;
}

void GameStateController::TogglePause()
{
    paused_ = !paused_;
}

bool GameStateController::IsPaused() const
{
    return paused_;
}
