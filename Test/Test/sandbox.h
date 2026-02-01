#pragma once
#include "dge.h"
#include "core/layer.h"
#include "core/log.h"
#include "core/file.h"
#include "stb_image.h"
#include "DGGL/shader.h"
#include "DGGL/texture.h"

class SandboxLayer : DGE::Layer
{
public:
	SandboxLayer();

	void onAttach() override;
	void onUpdate() override;
	void onDetach() override;
private:
	unsigned int triangleVBO;
	unsigned int triangleEBO;
	unsigned int vao;
	unsigned int wallTexture;
	Shader shaderProgram;
	int buffer;
};