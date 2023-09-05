#include "shader.h"

#include <iostream>

struct Shader::impl_t
{
    uint32_t m_id;
};

Shader::Shader(const std::string& shaderSource, GLenum shaderType)
{
    createImpl();
    impl().m_id = glCreateShader(shaderType);
    auto src = shaderSource.c_str();
    glShaderSource(impl().m_id, 1, &src, NULL);
    glCompileShader(impl().m_id);
}

Shader::~Shader()
{
    glDeleteShader(impl().m_id);
}

std::string Shader::error() const
{
    int success;
    char infoLog[512];

    glGetShaderiv(impl().m_id, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(impl().m_id, 512, NULL, infoLog);
        return infoLog;
    };

    return "no error";
}

uint32_t Shader::id() const
{
    return impl().m_id;
}

