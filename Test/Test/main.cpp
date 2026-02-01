#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/app.h"
#include "utils.h"
#include "sandbox.h"


int main(void)
{
    DGE::App app;
    (app.init(800, 600, "DGE"));
    print_opengl_properties();
    app.attachLayer((DGE::Layer*)(new SandboxLayer));
    (app.run());
    app.terminate();
    return 0;
}