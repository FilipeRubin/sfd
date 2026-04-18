#pragma once
#include <rendering/i-renderer-managed.h>
#include <rendering/resources/i-rendering-rule.h>
#include <math/matrix4x4.h>
#include <types/directional-light.h>

class OGLRenderingRule : public IRenderingRule, public IRendererManaged
{
public:
	OGLRenderingRule(const char* vertexShaderSource, const char* fragmentShaderSource);
	void Bind() override;
	void Create() override;
	void Destroy() override;
	void SetUniform(const char* name, const Vector3& value);
	void SetUniform(const char* name, const Vector4& value);
	void SetUniform(const char* name, const Color& value);
	void SetUniform(const char* name, const Matrix4x4& value);
private:
	unsigned int m_program;
	const char* m_vertexShaderSource;
	const char* m_fragmentShaderSource;
};
