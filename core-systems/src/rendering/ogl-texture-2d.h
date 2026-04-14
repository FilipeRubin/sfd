#pragma once
#include <rendering/i-texture-2d.h>
#include <math/vector2.h>
#include "i-renderer-managed.h"

class OGLTexture2D : public ITexture2D, public IRendererManaged
{
public:
	OGLTexture2D(const unsigned char* data, size_t dataSize, const Vector2& size);
	void Bind();
	Vector2 GetSize() override;
	void Create() override;
	void Destroy() override;
private:
	const unsigned char* m_data;
	size_t m_dataSize;
	Vector2 m_size;
	unsigned int m_texture;
};