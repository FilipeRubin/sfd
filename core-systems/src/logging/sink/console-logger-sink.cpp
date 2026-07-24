#include <logging/sink/console-logger-sink.h>
#include <iostream>

static inline constexpr std::string LogLevelAsString(const LogLevel& logLevel);

void ConsoleLoggerSink::Write(const LogMessage& logMessage)
{
	std::string level = LogLevelAsString(logMessage.level);
	std::cout << '[' << level << "] " << logMessage.message << '\n';
}

constexpr std::string LogLevelAsString(const LogLevel& logLevel)
{
	switch (logLevel)
	{
	case LogLevel::TRACE:
		return "Trace";
	case LogLevel::DEBUG:
		return "Debug";
	case LogLevel::INFO:
		return "Info";
	case LogLevel::WARNING:
		return "Warning";
	case LogLevel::ERROR:
		return "Error";
	case LogLevel::FATAL:
		return "Fatal";
	}
}