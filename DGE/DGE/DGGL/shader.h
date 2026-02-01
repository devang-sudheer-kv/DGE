#pragma once
#include "dge.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
public:
	Shader();

	void compile(const char* vertexSource, const char* fragmentSource);
	void use();
	// TODO:
	void clean();


	void setMat4(const std::string& name, glm::mat4 value) const;
	void setFloat(const std::string& name, float value) const;
private:
	unsigned int Id_;
};