#include "shader.h"
#include "core/log.h"
#include "glm/glm.hpp"

Shader::Shader() : Id_(0)
{ }

void Shader::compile(const char* vs, const char* fs)
{
    unsigned int vert;
    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vs, NULL);
    glCompileShader(vert);
    int success;
    char infoLog[512];
    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vert, 512, NULL, infoLog);
        MSG("ERROR COMPILING VERTEX SHADER" << infoLog);
    }

    unsigned int frag;
    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fs, NULL);
    glCompileShader(frag);

    char infoLog1[512];
    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(frag, 512, NULL, infoLog1);
        MSG("ERROR COMPILING FRAGMENT SHADER " << infoLog1);
    }


    Id_ = glCreateProgram();
    glAttachShader(Id_, vert);
    glAttachShader(Id_, frag);
    glLinkProgram(Id_);
    int linkSuccess;
    char linkLog[512] = {};
    glGetProgramiv(Id_, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess)
    {
        glGetProgramInfoLog(Id_, 512, NULL, linkLog);
        MSG("ERROR LINKING" << linkLog);
    }
    glUseProgram(Id_);
    glDeleteShader(vert);
    glDeleteShader(frag);
    glUseProgram(0);
}

void Shader::use()
{
    //MSG_DBG(Id_);
    glUseProgram(Id_);
}

void Shader::clean()
{
    glUseProgram(0);
    glDeleteProgram(Id_);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(Id_, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(Id_, name.c_str()) , 1, GL_FALSE, glm::value_ptr(value));
}