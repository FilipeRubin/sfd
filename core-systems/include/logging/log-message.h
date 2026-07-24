#pragma once
#include "log-level.h"
#include <string>

struct LogMessage
{
	LogLevel level;
	std::string message;
};
