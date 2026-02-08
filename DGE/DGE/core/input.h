#pragma once


#include "dge.h"
#include "app.h"

namespace DGE {
	#define DGE_INPUT_MAX_KEYS = 512;
	#define DGE_INPUT_MAX_MOUSE_BUTTONS = 8;

	class Input {
	private:
		static GLFWwindow* window_;

	public:

        static bool IsKeyDown(int key)
        {
            return glfwGetKey(App::getWindow(), key) == GLFW_PRESS;
        }

        static bool IsMouseButtonDown(int button)
        {
            return glfwGetMouseButton(App::getWindow(), button) == GLFW_PRESS;
        }

        static glm::vec2 GetMousePos()
        {
            double x, y;
            glfwGetCursorPos(App::getWindow(), &x, &y);
            return { (float)x, (float)y };
        }
	};
}