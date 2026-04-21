#pragma once

class SourceContainer
{
public:
	SourceContainer();
	SourceContainer(const SourceContainer& other) = delete;
	SourceContainer(SourceContainer&& other) noexcept;
	~SourceContainer();
	SourceContainer& operator=(const SourceContainer& other) = delete;
	SourceContainer& operator=(SourceContainer&& other) noexcept;
	const char* GetSource(unsigned int index) const;
	size_t GetSourceCount() const;
	void SetSources(const char** const sources, size_t sourceCount);
private:
	char** m_sources;
	size_t m_sourceCount;
};
