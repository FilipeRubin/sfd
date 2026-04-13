#pragma once
#include <i-window.h>
#include "input/win32-basic-input.h"
#include "win32-window-class.h"

class Win32Window : public IWindow
{
public:
	Win32Window();
	void Finalize() override;
	void Process() override;
	bool ShouldClose() const override;
	bool IsInitialized() const override;
	bool TryInitialize(const WindowParameters& parameters) override;
	const IBasicInput* GetBasicInput() const override;
	WindowSizeCallback GetWindowSizeCallback() const override;
	void SetWindowSizeCallback(WindowSizeCallback windowSizeCallback) override;
	void Close();
	const void* GetHandle() const;
private:
	static unsigned int s_instanceCount;
	static Win32WindowClass s_windowClass;
	static bool TryIncrement();
	static void Decrement();
	bool m_shouldClose;
	void* m_hwnd;
	Win32BasicInput m_basicInput;
	WindowSizeCallback m_windowSizeCallback;
};