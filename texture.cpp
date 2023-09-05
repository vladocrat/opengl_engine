#include "texture.h"

#include "opengl.h"
#include "utils.h"

struct Texture::impl_t
{
    uint32_t m_id;
};

Texture::Texture(const std::string_view& path)
{
    //! TODO needs to be generalized, i.g. different texture types, parameters and so on...
    createImpl();
    glGenTextures(1, &impl().m_id);
    glBindTexture(GL_TEXTURE_2D, impl().m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto image = Utils::readImage(path);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{

}
