#include "App.h"
#include <iostream>

int main()
{
    App app;
    if (!app.Initialize())
    {
        app.Shutdown();
        return 1;
    }
    app.Run();
    app.Shutdown();
    return 0;
}
