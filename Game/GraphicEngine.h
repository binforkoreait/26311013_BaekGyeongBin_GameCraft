#pragma once

class GraphicEngine
{
public:
    bool Initialize(int (*update)(), int (*render)());
    int Run();
    void Shutdown();
};
