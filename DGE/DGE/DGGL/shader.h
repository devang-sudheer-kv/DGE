#pragma once
#include "dge.h"


class Shader
{
public:
	Shader();

	void compile(const char* vertexSource, const char* fragmentSource);
	void use();
	// TODO:
	void clean();

	void setFloat(const std::string& name, float value) const;
private:
	unsigned int m_ID;
};