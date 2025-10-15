#pragma once
#include "window-parameters.h"

class IWindow
{
public:
	virtual ~IWindow() = default;
	virtual void Finalize() = 0;
	virtual void Process() = 0;
	virtual bool ShouldClose() const = 0;
	virtual bool IsInitialized() const = 0;
	virtual bool TryInitialize(const WindowParameters& parameters = {}) = 0;
};
