#pragma once
#include <rendering/i-renderer-resource-manager.h>
#include <rendering/i-renderer-managed.h>
#include <ogl-graphics-backend.h>
#include <list>
#include <memory>
#include <utility>

using std::list;
using std::unique_ptr;

class OGLRendererResourceManager : public IRendererResourceManager
{
public:
	OGLRendererResourceManager(OGLGraphicsBackend* backend);
	~OGLRendererResourceManager();
	INDCRenderingRule* CreateNDCRenderingRule() override;
	IBasic3DRenderingRule* CreateBasic3DRenderingRule() override;
	INDCShape* CreateNDCShape(float* vertices, size_t length) override;
	IBasic3DMesh* CreateBasic3DMesh(float* vertices, size_t verticesLength, unsigned int* indices, size_t indicesLength) override;
	void Update();
private:
	OGLGraphicsBackend* m_backend;
	list<unique_ptr<IRendererManaged>> m_waitingToCreate;
	list<unique_ptr<IRendererManaged>> m_resources;

	template<typename T, typename... Args>
	inline T* CreateResource(Args&&... args)
	{
		bool isCurrentBackend = OGLGraphicsBackend::GetCurrent() == m_backend;
		list<unique_ptr<IRendererManaged>>& container = isCurrentBackend ? m_resources : m_waitingToCreate;
		unique_ptr<T> renderingRule = std::make_unique<T>(std::forward<Args>(args)...);
		if (isCurrentBackend)
		{
			renderingRule->Create();
		}
		T* result = static_cast<T*>(renderingRule.get());
		container.emplace_back(std::move(renderingRule));
		return result;
	}
};
