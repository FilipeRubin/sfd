#pragma once

class Win32WindowClass final
{
public:
	void* GetInstanceHandle() const;
	const wchar_t* GetWindowClassName() const;
	bool IsActive() const;
	bool TryRegister(const wchar_t* className);
	void Unregister();
private:
	void* m_hInstance;
	const wchar_t* m_className;
};