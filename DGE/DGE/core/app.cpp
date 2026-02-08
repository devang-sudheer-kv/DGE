#include "app.h"
#include "renderer/camera.h" // TODO: TEMP
#include "core/file.h"
#include <filesystem>

namespace DGE 
{
    GLFWwindow* App::window = nullptr;

    void resizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }


    App::App() {
    }

    App::~App() {

    }

    void App::onEvent(Event& e)
    {
        for (auto& layer : m_layerStack)
        {
            layer->onEvent(e);
        }
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
        glfwSetWindowUserPointer(window, this);


        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            MSG("Failed to load glad");
            return;
        }
        // callbacks
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto* app = static_cast<App*>(glfwGetWindowUserPointer(window));

            if (action == GLFW_PRESS)
            {
                KeyPressEvent e(key);
                app->onEvent(e);
            }
            else if (action == GLFW_RELEASE)
            {
                //KeyReleaseEvent e(key);
                //app->onEvent(e);
            }
            });
        glfwSetWindowSizeCallback(window, resizeCallback);

        glViewport(0, 0, width, height);
    }

    void App::run()
    {
        while (!glfwWindowShouldClose(window))
        {
            update();
            for (auto& layer : m_layerStack)
            {
                layer->onUpdate();
            }
        /* Swap front and back buffers */
        glfwSwapInterval(1);
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        }

    }

    void App::update()
    {
    }

    void App::terminate()
    {
        for (auto& layer : m_layerStack)
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