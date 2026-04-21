#pragma once
#include <rendering/resources/i-texture-2d.h>
#include <types/dimensions.h>
#include <types/color8.h>
#include <rendering/i-renderer-managed.h>

class OGLTexture2D : public ITexture2D, public IRendererManaged
{
public:
	OGLTexture2D(const Color8* data, const Dimensions& dimensions);
	~OGLTexture2D();
	void Bind() override;
	void Create() override;
	void Destroy() override;
private:
	Color8* m_data;
	Dimensions m_dimensions;
	unsigned int m_texture;
};