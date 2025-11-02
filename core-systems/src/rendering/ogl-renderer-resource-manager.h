#pragma once
#include <rendering/i-renderer-resource-manager.h>
#include <rendering/i-renderer-managed.h>
#include <ogl-graphics-backend.h>
#include <list>
#include <memory>

using std::list;
using std::unique_ptr;

class OGLRendererResourceManager : public IRendererResourceManager
{
public:
	OGLRendererResourceManager(OGLGraphicsBackend* backend);
	~OGLRendererResourceManager();
	INDCRenderingRule* CreateNDCRenderingRule() override;
	INDCShape* CreateNDCShape(float* vertices, size_t length) override;
	void Update();
private:
	OGLGraphicsBackend* m_backend;
	list<unique_ptr<IRendererManaged>> m_waitingToCreate;
	list<unique_ptr<IRendererManaged>> m_resources;
};
