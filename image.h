#pragma once

#include <type_traits>

#include "stb_image.h"

struct Image
{
    virtual ~Image()
    {
        stbi_image_free(data);
    }

    int32_t width;
    int32_t height;
    uint8_t* data;
    int32_t nrChannels;
};

