#pragma once
#include <rendering/i-texture-2d.h>
#include <types/dimensions.h>
#include <types/color8.h>
#include "i-renderer-managed.h"

class OGLTexture2D : public ITexture2D, public IRendererManaged
{
public:
	OGLTexture2D(Color8* data, size_t dataSize, const Dimensions& size);
	void Bind() override;
	void Create() override;
	void Destroy() override;
private:
	Color8* m_data;
	size_t m_dataSize;
	Dimensions m_size;
	unsigned int m_texture;
};