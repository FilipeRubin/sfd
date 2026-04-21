#include <containers/source-container.h>
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#undef _CRT_SECURE_NO_WARNINGS

SourceContainer::SourceContainer() :
    m_sources(nullptr),
    m_sourceCount(0ULL)
{
}

SourceContainer::SourceContainer(SourceContainer&& other) noexcept :
    m_sources(other.m_sources),
    m_sourceCount(other.m_sourceCount)
{
    if (this != &other)
    {
        other.m_sources = nullptr;
        other.m_sourceCount = 0ULL;
    }
}

SourceContainer::~SourceContainer()
{
    for (unsigned long long i = 0ULL; i < m_sourceCount; i++)
    {
        delete[] m_sources[i];
    }
    delete[] m_sources;
}

SourceContainer& SourceContainer::operator=(SourceContainer&& other) noexcept
{
    if (this != &other)
    {
        for (unsigned long long i = 0ULL; i < m_sourceCount; i++)
        {
            delete[] m_sources[i];
        }
        delete[] m_sources;
        
        m_sources = other.m_sources;
        m_sourceCount = other.m_sourceCount;
        
        other.m_sources = nullptr;
        other.m_sourceCount = 0ULL;
    }
    return *this;
}

const char* SourceContainer::GetSource(unsigned int index) const
{
    return m_sources[index];
}

size_t SourceContainer::GetSourceCount() const
{
    return m_sourceCount;
}

void SourceContainer::SetSources(const char** const sources, size_t sourceCount)
{
    for (unsigned long long i = 0ULL; i < m_sourceCount; i++)
    {
        delete[] m_sources[i];
    }
    delete[] m_sources;

    m_sources = new char*[sourceCount];
    m_sourceCount = sourceCount;
    for (unsigned long long i = 0ULL; i < sourceCount; i++)
    {
        size_t sourceLength = std::strlen(sources[i]) + 1ULL;
        m_sources[i] = new char[sourceLength];
        std::strcpy(m_sources[i], sources[i]);
    }
}
