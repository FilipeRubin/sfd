#pragma once
#include "sink/i-logger-sink.h"
#include <memory>

class Logger
{
public:
	static void Log(const LogMessage& logMessage);
	static void SetSink(std::unique_ptr<ILoggerSink> sink);
private:
	static std::unique_ptr<ILoggerSink> s_sink;
};
