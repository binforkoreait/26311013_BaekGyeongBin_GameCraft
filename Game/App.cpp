#include "App.h"
App* App::instance_ = nullptr;

bool App::Initialize()
{
    instance_ = this;
    if (!graphicEngine_.Initialize(Update, Render))
    {
        return false;
    }
    return game_.Initialize();
}

int App::Run()
{
    return graphicEngine_.Run();
}

void App::Shutdown()
{
    game_.Shutdown();
    graphicEngine_.Shutdown();
    instance_ = nullptr;
}

int App::Update()
{
    return instance_->game_.Update();
}

int App::Render()
{
    return instance_->game_.Render();
}
