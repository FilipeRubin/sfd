#pragma once
#include <containers/fixed-array.h>
#include <utils/shared.h>
#include <types/dimensions.h>
#include <types/color8.h>
#include <rendering/resources/i-texture-2d.h>
#include <rendering/i-renderer-managed.h>

class OGLTexture2D : public ITexture2D, public IRendererManaged
{
public:
	OGLTexture2D(Shared<FixedArray<Color8>> data, const Dimensions& dimensions);
	OGLTexture2D(const OGLTexture2D& other) = delete;
	OGLTexture2D(OGLTexture2D&& other) noexcept = delete;
	OGLTexture2D& operator=(const OGLTexture2D& other) = delete;
	OGLTexture2D& operator=(OGLTexture2D&& other) noexcept = delete;
	void Bind() override;
	const Dimensions& GetDimensions() const override;
	bool IsValid() const override;
	void Create() override;
	void Destroy() override;
private:
	Shared<FixedArray<Color8>> m_data;
	const Dimensions& m_dimensions;
	unsigned int m_texture;
};