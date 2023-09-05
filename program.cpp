#include "program.h"

#include "opengl.h"

struct Program::impl_t
{
    uint32_t m_id;
};

Program::Program()
{
    createImpl();
    impl().m_id = glCreateProgram();
}

Program::~Program()
{
    glDeleteProgram(impl().m_id);
}

void Program::attach(const Shader& shader)
{
    glAttachShader(impl().m_id, shader.id());
}

void Program::link()
{
    glLinkProgram(impl().m_id);
}

void Program::use()
{
    glUseProgram(impl().m_id);
}

uint32_t Program::id() const
{
    return impl().m_id;
}

std::string Program::error() const
{
    int success;
    char infoLog[512];

    glGetProgramiv(impl().m_id, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(impl().m_id, 512, NULL, infoLog);
        return infoLog;
    }

    return "no error";
}
