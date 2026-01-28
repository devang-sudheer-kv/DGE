#include "shader.h"
#include "core/log.h"

Shader::Shader() : m_ID(0)
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

    int linkSuccess;
    char linkLog[512] = {};
    glGetProgramiv(m_ID, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, linkLog);
        MSG("ERROR LINKING" << linkLog);
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vert);
    glAttachShader(m_ID, frag);
    glLinkProgram(m_ID);
    glUseProgram(m_ID);
    glDeleteShader(vert);
    glDeleteShader(frag);
    glUseProgram(0);
}

void Shader::use()
{
    glUseProgram(m_ID);
}

void Shader::clean()
{
    glUseProgram(0);
    glDeleteProgram(m_ID);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}