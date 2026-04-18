#include "ogl-renderer-resource-manager.h"
#include "resources/ogl-rendering-rule.h"
#include "resources/ogl-mesh-3d.h"
#include "resources/ogl-texture-2d.h"

#include <data/lambert-shader.h>
#include <data/red-shader.h>

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
    OGLRenderingRule* resource = CreateResource<OGLRenderingRule>(lambertVertexShaderSource, lambertFragmentShaderSource);

    // TEMPORARY
    resource->Bind();

    resource->SetUniform("u_model", Matrix4x4::RotationY(3.1415f / 5.0f));
    resource->SetUniform("u_view", Matrix4x4::RotationX(3.1415 / 4.0f) * Matrix4x4::Translation({ 0.0f, -10.0f, -10.0f }));
    resource->SetUniform("u_projection", Matrix4x4::Perspective(16.0f / 9.0f, 3.1415f / 2.0f, 0.1f, 100.0f));

    resource->SetUniform("u_ambientLight", Color(0.1f, 0.2f, 0.4f));
    resource->SetUniform("u_directionalLightDiffuse", Color(1.0f, 1.0f, 1.0f));
    resource->SetUniform("u_directionalLightDirection", Vector3(0.0f, -1.0f, -1.0f));

    return resource;
}

IRenderingRule* OGLRendererResourceManager::CreateRedRenderingRule()
{
    OGLRenderingRule* resource = CreateResource<OGLRenderingRule>(redVertexShaderSource, redFragmentShaderSource);

    // TEMPORARY
    resource->Bind();

    resource->SetUniform("u_model", Matrix4x4::RotationY(3.1415f / 5.0f));
    resource->SetUniform("u_view", Matrix4x4::RotationX(3.1415 / 4.0f) * Matrix4x4::Translation({ 0.0f, -10.0f, -10.0f }));
    resource->SetUniform("u_projection", Matrix4x4::Perspective(16.0f / 9.0f, 3.1415f / 2.0f, 0.1f, 100.0f));

    return resource;
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
