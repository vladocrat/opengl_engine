#pragma once

#include "opengl.h"
#include "pimpl.h"

#include <string>

class Shader
{
public:
    Shader(const std::string& shaderSrc, GLenum shaderType);
    virtual ~Shader();

    [[nodiscard]] std::string error() const;
    [[nodiscard]] uint32_t id() const;

private:
    DECLARE_PIMPL
};

