#pragma once
#include "dge.h"
#include "DGGL/shader.h"
namespace DGE
{
	constexpr int MAX_RECT_PER_BATCH = 10000;
	struct Rect {
		float x, y, w, h;
		uint8_t r, g, b, a;
		Rect(float x_, float y_, float w_, float h_, uint8_t r_=255, uint8_t g_=255, uint8_t b_=255, uint8_t a_ = 255) : x(x_), y(y_), w(w_), h(h_), r(r_), g(g_), b(b_), a(a_) {}
	};

	struct AttribInfo {
		uint32_t index;
		uint32_t length;
		uint32_t type;
		uint8_t normalized;
		AttribInfo(uint32_t i, uint32_t l, uint32_t t, bool n = GL_FALSE)
			: index(i), length(l), type(t), normalized(n) {
		}
	};

	void configAttribs(uint32_t vboId, uint32_t vaoId, std::vector<AttribInfo>);

	class Renderer2D
	{
	private:
		uint32_t rectVAO;
		uint32_t rectVBO;
		uint32_t rectInstanceVBO;
		Shader defaultRectShader;
		std::vector<Rect> rectRenderBuffer;
		
		// TODO: CAMERA
		glm::mat4 view;
		glm::mat4 projection;
	public:
		Renderer2D();
		~Renderer2D();
		void init();
		void beginBatch();
		// adds rectangle to rendering queue
		void addRect(float x, float y, float w, float h, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255);
		void renderBatch();
	};
}