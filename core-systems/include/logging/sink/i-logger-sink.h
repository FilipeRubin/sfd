#pragma once
#include "../log-message.h"

class ILoggerSink
{
public:
	virtual ~ILoggerSink() = default;
	virtual void Write(const LogMessage& logMessage) = 0;
};
