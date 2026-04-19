#pragma once
#include <rendering/i-renderer-parameter-manager.h>
#include "resources/ogl-rendering-rule.h"
#include <list>
#include <memory>
#include <utility>

class OGLRendererParameterManager : public IRendererParameterManager
{
public:
	ICamera3DParameter* CreateCamera3D() override;
	IDirectionalLightParameter* CreateDirectionalLight() override;
	ITransform3DParameter* CreateTransform3D() override;
private:
	std::list<std::unique_ptr<IRenderParameter>> m_parameters;
	template<typename T, typename... Args>
	inline T* CreateParameter(Args&&... args)
	{
		std::unique_ptr<T> parameter = std::make_unique<T>(std::forward<Args>(args)...);
		T* result = static_cast<T*>(parameter.get());
		m_parameters.emplace_back(std::move(parameter));
		return result;
	}
};