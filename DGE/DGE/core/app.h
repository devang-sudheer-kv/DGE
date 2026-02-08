#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "core/log.h"
#include "DGGL/shader.h"
#include "stb_image.h"
#include "core/layer.h"

namespace DGE {
	class App {
	public:
		App();
		~App();

		void init(int width, int height, const char* title);
		void run();
		void terminate();
		void attachLayer(Layer* layer);
		void onEvent(Event& e);
		static GLFWwindow* getWindow() { return window; };


	private:
		static GLFWwindow* window;
		std::vector<Layer*> m_layerStack;
		void update();
	};
}