#pragma once
#include "i-logger-sink.h"

class ConsoleLoggerSink : public ILoggerSink
{
public:
	void Write(const LogMessage& logMessage) override;
};
