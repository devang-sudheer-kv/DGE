#pragma once
#include "dge.h"
#include "DGGL/shader.h"

namespace DGE
{
	class Renderer2D
	{
	private:
		unsigned int rectVAO;
		unsigned int rectVBO;
		unsigned int rectEBO;
		Shader defaultRectShader;

	public:
		Renderer2D();
		~Renderer2D();
		void init();
	};
}