#include "ogl-renderer-resource-manager.h"
#include "resources/ogl-rendering-rule.h"
#include "resources/ogl-mesh-3d.h"
#include "resources/ogl-texture-2d.h"

#include <data/lambert-shader.h>
#include <data/unshaded-shader.h>

using std::unique_ptr;
using std::list;

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

IRenderingRule* OGLRendererResourceManager::CreateLambertRenderingRule()
{
    return CreateResource<OGLRenderingRule>(lambertVertexShaderSource, lambertFragmentShaderSource);
}

IRenderingRule* OGLRendererResourceManager::CreateUnshadedRenderingRule()
{
    return CreateResource<OGLRenderingRule>(unshadedVertexShaderSource, unshadedFragmentShaderSource);;
}

IMesh3D* OGLRendererResourceManager::Create3DMesh(Vertex3D* vertices, size_t verticesLength, unsigned int* indices, size_t indicesLength)
{
    return CreateResource<OGLMesh3D>(reinterpret_cast<float*>(vertices), verticesLength, indices, indicesLength);;
}

ITexture2D* OGLRendererResourceManager::CreateTexture2D(Color8* data, size_t dataLength, const Dimensions& size)
{
    return CreateResource<OGLTexture2D>(data, dataLength, size);
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
