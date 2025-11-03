#include "ogl-renderer-resource-manager.h"
#include "ogl-ndc-rendering-rule.h"
#include "ogl-ndc-shape.h"
#include "ogl-basic-3d-rendering-rule.h"
#include "ogl-basic-3d-mesh.h"

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
    return CreateResource<OGLNDCRenderingRule>();
}

IBasic3DRenderingRule* OGLRendererResourceManager::CreateBasic3DRenderingRule()
{
    return CreateResource<OGLBasic3DRenderingRule>();
}

INDCShape* OGLRendererResourceManager::CreateNDCShape(float* vertices, size_t length)
{
    return CreateResource<OGLNDCShape>(vertices, length);
}

IBasic3DMesh* OGLRendererResourceManager::CreateBasic3DMesh(float* vertices, size_t verticesLength, unsigned int* indices, size_t indicesLength)
{
    return CreateResource<OGLBasic3DMesh>(vertices, verticesLength, indices, indicesLength);
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
