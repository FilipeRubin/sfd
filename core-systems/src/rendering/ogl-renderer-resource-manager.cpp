#include "ogl-renderer-resource-manager.h"
#include "ogl-ndc-rendering-rule.h"
#include "ogl-ndc-shape.h"

OGLRendererResourceManager::OGLRendererResourceManager(OGLGraphicsBackend* backend) :
    m_backend(backend),
    m_waitingToCreate(list<unique_ptr<IRendererManaged>>()),
    m_resources(list<unique_ptr<IRendererManaged>>())
{
}

OGLRendererResourceManager::~OGLRendererResourceManager()
{
    OGLGraphicsBackend* currentBackend = OGLGraphicsBackend::GetCurrent();
    
    if (currentBackend != m_backend)
    {
        m_backend->MakeCurrent();
    }
    else
    {
        for (unique_ptr<IRendererManaged>& managed : m_waitingToCreate)
        {
            managed->Destroy();
        }
        m_waitingToCreate.clear();
    }

    for (unique_ptr<IRendererManaged>& managed : m_resources)
    {
        managed->Destroy();
    }
    m_resources.clear();

    if (currentBackend != m_backend)
        currentBackend->MakeCurrent();
}

INDCRenderingRule* OGLRendererResourceManager::CreateNDCRenderingRule()
{
    bool isCurrentBackend = OGLGraphicsBackend::GetCurrent() == m_backend;
    list<unique_ptr<IRendererManaged>>& container = isCurrentBackend ? m_resources : m_waitingToCreate;
    unique_ptr<OGLNDCRenderingRule> renderingRule = std::make_unique<OGLNDCRenderingRule>();
    if (isCurrentBackend)
    {
        renderingRule->Create();
    }
    OGLNDCRenderingRule* result = static_cast<OGLNDCRenderingRule*>(renderingRule.get());
    container.emplace_back(std::move(renderingRule));
    return result;
}

INDCShape* OGLRendererResourceManager::CreateNDCShape(float* vertices, size_t length)
{
    bool isCurrentBackend = OGLGraphicsBackend::GetCurrent() == m_backend;
    list<unique_ptr<IRendererManaged>>& container = isCurrentBackend ? m_resources : m_waitingToCreate;
    unique_ptr<OGLNDCShape> shape = std::make_unique<OGLNDCShape>(vertices, length);
    if (isCurrentBackend)
    {
        shape->Create();
    }
    INDCShape* result = static_cast<INDCShape*>(shape.get());
    container.emplace_back(std::move(shape));
    return result;
}

void OGLRendererResourceManager::Update()
{
    for (unique_ptr<IRendererManaged>& managed : m_waitingToCreate)
    {
        managed->Create();
        m_resources.push_back(std::move(managed));
    }

    m_waitingToCreate.clear();
}
