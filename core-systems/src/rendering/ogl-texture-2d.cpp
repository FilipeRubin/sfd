#include "ogl-texture-2d.h"
#include <ogl.h>

OGLTexture2D::OGLTexture2D(const unsigned char* data, size_t dataSize, const Dimensions& size) :
    m_data(data),
    m_dataSize(dataSize),
    m_size(size),
    m_texture(0U)
{
}

void OGLTexture2D::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

Dimensions OGLTexture2D::GetSize()
{
    return m_size;
}

void OGLTexture2D::Create()
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void OGLTexture2D::Destroy()
{
    glDeleteTextures(1, &m_texture);
}
