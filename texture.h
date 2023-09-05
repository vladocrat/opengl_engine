#pragma once

#include "pimpl.h"

#include <string_view>

class Texture
{
public:
    Texture(const std::string_view& path);
    virtual ~Texture();

private:
    DECLARE_PIMPL
};
