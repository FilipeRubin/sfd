#pragma once
#include <rendering/i-renderer-resource-manager.h>
#include <rendering/i-renderer-managed.h>
#include <ogl-graphics-backend.h>
#include <list>
#include <memory>
#include <utility>

class OGLRendererResourceManager : public IRendererResourceManager
{
public:
	OGLRendererResourceManager(OGLGraphicsBackend* backend);
	~OGLRendererResourceManager();
	IRenderingRule* CreateLambertRenderingRule() override;
	IRenderingRule* CreateUnshadedRenderingRule() override;
	IMesh3D* Create3DMesh(const IMesh3DGenerator& generator) override;
	ITexture2D* CreateTexture2D(Color8* data, size_t dataLength, const Dimensions& size) override;
	void Update();
private:
	OGLGraphicsBackend* m_backend;
	std::list<std::unique_ptr<IRendererManaged>> m_waitingToCreate;
	std::list<std::unique_ptr<IRendererManaged>> m_resources;
	
	template<typename T, typename... Args>
	inline T* CreateResource(Args&&... args)
	{
		bool isCurrentBackend = OGLGraphicsBackend::GetCurrent() == m_backend;
		std::list<std::unique_ptr<IRendererManaged>>& container = isCurrentBackend ? m_resources : m_waitingToCreate;
		std::unique_ptr<T> resource = std::make_unique<T>(std::forward<Args>(args)...);
		if (isCurrentBackend)
		{
			resource->Create();
		}
		T* result = static_cast<T*>(resource.get());
		container.emplace_back(std::move(resource));
		return result;
	}
};
