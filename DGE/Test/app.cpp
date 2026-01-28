#include "app.h"
#include "core/file.h"
#include <filesystem>

namespace DGE 
{
    void resizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }


    App::App() : window(nullptr) {
    }

    App::~App() {

    }

    void App::attachLayer(Layer* layer)
    {
        layer->onAttach();
        m_layerStack.push_back(layer);
    }

    void App::init(int width, int height, const char* title)
    {
        /* Initialize the library */
        if (!glfwInit())
        {
            MSG("Failed to init GLFW");
            return;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window)
        {
            MSG("Failed to create a window");
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            MSG("Failed to load glad");
            return;
        }

        glViewport(0, 0, width, height);
        glfwSetWindowSizeCallback(window, resizeCallback);
    }

    void App::run()
    {
        while (!glfwWindowShouldClose(window))
        {
            update();
            for (auto layer : m_layerStack)
            {
                layer->onUpdate();
            }
        }

    }

    void App::update()
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    void App::terminate()
    {
        for (auto layer : m_layerStack)
        {
            if (layer != nullptr)
            {
                layer->onDetach();
                delete layer;
            }
        }
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}