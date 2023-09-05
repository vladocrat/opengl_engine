#include "utils.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "stb_image.h"

namespace Utils
{

bool readFile(const std::string_view& path, std::string& shader)
{
    std::ifstream file;
    file.open(std::string(path));

    if (!file.is_open())
    {
        std::cerr << "ERROR::SHADER::FAILED_TO_OPEN_SHADER_FILE" << std::endl;
        return false;
    }

    std::stringstream stream;
    stream << file.rdbuf();

    file.close();
    shader = stream.str();
    return true;
}

Image readImage(const std::string_view& path, int32_t desiredChannels)
{
    Image image;
    auto data = stbi_load(path.data(), &image.width, &image.height, &image.nrChannels, desiredChannels);
    image.data = data;
    return image;
}

} //! Utils
