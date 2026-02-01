#include "renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "core/file.h"

namespace DGE
{
	static uint32_t sizeOfGLType(uint32_t type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_INT:   return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_SHORT: return 2;
		case GL_UNSIGNED_BYTE: return 1;
		default: return 0; // or assert
		}
	}

	void configAttribs(uint32_t vboId, uint32_t vaoId, std::vector<AttribInfo> attribs)
	{
		glBindVertexArray(vaoId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);

		// calculate stride
		int32_t stride=0;
		for (const auto& a : attribs)
		{
			stride += a.length*sizeOfGLType(a.type);
		}
		// set attribs one by one
		int32_t offset = 0;
		for (const auto& a : attribs)
		{
			glVertexAttribPointer(a.index, a.length, a.type, a.normalized,stride, (const void*)(uintptr_t)offset);
			glEnableVertexAttribArray(a.index);
			offset += a.length * sizeOfGLType(a.type);
		}
	}

	Renderer2D::Renderer2D()
	{

	}

	Renderer2D::~Renderer2D()
	{

	}



	void Renderer2D::init()
	{
		rectRenderBuffer.reserve(1000);
		float vertices[] = {
			0.5f, 0.5f,
			-0.5f, -0.5f,
			-0.5f, 0.5f, 
			0.5f, 0.5f,  
			0.5f, -0.5f, 
			-0.5f, -0.5f,
		};

		glGenVertexArrays(1, &rectVAO);
		glGenBuffers(1, &rectVBO);
		glGenBuffers(1, &rectInstanceVBO);

		glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, rectInstanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Rect) * MAX_RECT_PER_BATCH, nullptr, GL_DYNAMIC_DRAW);

		std::vector<AttribInfo> rectAttribs;
		rectAttribs.emplace_back(0, 2, GL_FLOAT);
		configAttribs(rectVBO, rectVAO, rectAttribs);

		std::vector<AttribInfo> rectInstanceAttribs;
		rectInstanceAttribs.emplace_back(1, 4, GL_FLOAT);
		rectInstanceAttribs.emplace_back(2, 4, GL_UNSIGNED_BYTE, GL_TRUE);
		configAttribs(rectInstanceVBO, rectVAO, rectInstanceAttribs);
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);

		const char* vert_source = R"(
#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aTransform;
layout (location = 2) in vec4 aCol;

uniform mat4 view;
uniform mat4 projection;

out vec4 col;

void main()
{
	col = aCol;
	gl_Position = projection * vec4(aPos * aTransform.zw + aTransform.xy, 0.0f, 1.0);
}
)";
		const char* frag_source = R"(
#version 330 core

out vec4 FragColor;
in vec4 col;

void main()
{
	FragColor = col;
}
)";
		defaultRectShader.compile(vert_source, frag_source);

		projection = glm::ortho(-200.0f, 200.0f, -200.0f, 200.0f, -1.0f, 100.0f);
		defaultRectShader.use();
		defaultRectShader.setMat4("projection", projection);
	}

	void Renderer2D::beginBatch()
	{
		rectRenderBuffer.clear();
	}

	void Renderer2D::addRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		rectRenderBuffer.emplace_back(x, y, w, h, r, g, b, a);
	}

	void Renderer2D::renderBatch()
	{
		defaultRectShader.use();
		glBindVertexArray(rectVAO);
		glBindBuffer(GL_ARRAY_BUFFER, rectInstanceVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Rect) * rectRenderBuffer.size(), rectRenderBuffer.data());
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, rectRenderBuffer.size());
	}
}