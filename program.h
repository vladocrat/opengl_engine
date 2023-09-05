#pragma once

#include "shader.h"
#include "pimpl.h"

class Program final
{
public:
    Program();
    ~Program();

    void attach(const Shader& shader);
    void link();
    void use();

    [[nodiscard]] uint32_t id() const;
    [[nodiscard]] std::string error() const;
private:
    DECLARE_PIMPL
};


