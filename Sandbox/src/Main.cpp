#include "Application.h"
#include "Renderer.h"

int main()
{
    Application app;
    Renderer::Init();

    app.Run();
}