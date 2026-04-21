#include "ogl-texture-2d.h"
#include <ogl.h>
#include <cstring>

OGLTexture2D::OGLTexture2D(const Color8* data, const Dimensions& dimensions) :
    m_data(nullptr),
    m_dimensions(dimensions),
    m_texture(0U)
{
    size_t pixelCount = size_t(dimensions.x) * size_t(dimensions.y);
    m_data = new Color8[pixelCount];
    std::memcpy(m_data, data, size_t(dimensions.x) * size_t(dimensions.y) * sizeof(Color8));
}

OGLTexture2D::~OGLTexture2D()
{
    delete[] m_data;
}

void OGLTexture2D::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void OGLTexture2D::Create()
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_dimensions.x, m_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void OGLTexture2D::Destroy()
{
    glDeleteTextures(1, &m_texture);
}
