#pragma once
#include "Game.h"
#include "GraphicEngine.h"

class App
{
public:
    bool Initialize();
    int Run();
    void Shutdown();

private:
    static int Update();
    static int Render();
    static App* instance_;
    GraphicEngine graphicEngine_;
    Game game_;
};
