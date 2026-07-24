#include <logging/logger.h>
#include <logging/sink/console-logger-sink.h>

std::unique_ptr<ILoggerSink> Logger::s_sink = std::make_unique<ConsoleLoggerSink>();

void Logger::Log(const LogMessage& logMessage)
{
	s_sink->Write(logMessage);
}

void Logger::SetSink(std::unique_ptr<ILoggerSink> sink)
{
	s_sink = std::move(sink);
}
