#include "GraphicEngine.h"
#include <glc2d.h>
#if defined(_DEBUG)
#if defined(_M_X64)
#pragma comment(lib, "glc2d_x64_debug.lib")
#else
#pragma comment(lib, "glc2d_win32_debug.lib")
#endif
#else
#if defined(_M_X64)
#pragma comment(lib, "glc2d_x64_release.lib")
#else
#pragma comment(lib, "glc2d_win32_release.lib")
#endif
#endif
bool GraphicEngine::Initialize(int (*update)(), int (*render)())
{
    if (g2_InitSdk() < 0)
    {
        return false;
    }
    g2_SetFrameMove(update);
    g2_SetRender(render);
    g2_SetClearColor(0xFF202630);
    return g2_CreateWin(80, 60, 1280, 720, "Game", true, 1.0f) >= 0;
}

int GraphicEngine::Run()
{
    return g2_Run();
}

void GraphicEngine::Shutdown()
{
    g2_DestroyWin();
}
