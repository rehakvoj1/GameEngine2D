#include <iomanip>
#include <chrono>
#include <iostream>

#include "Log.h"

namespace GE2D
{
void Log::Init()
{
	GE2D_INFO("Logger initialized...");
}

void Log::Print(LogLevel level, const std::string& tag, const std::string& message)
{
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);

	tm localTime{};
	localtime_s(&localTime, &time);

	std::cout
		<< LevelToColor(level)
		<< "["
		<< std::put_time(&localTime, "%H:%M:%S")
		<< "] "
		<< "["
		<< tag
		<< "] "
		<< "["
		<< LevelToString(level)
		<< "] "
		<< message
		<< "\033[0m"
		<< std::endl;
}

const char* Log::LevelToString(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Trace: return "TRACE";
	case LogLevel::Info:  return "INFO";
	case LogLevel::Warn:  return "WARN";
	case LogLevel::Error: return "ERROR";
	case LogLevel::Fatal: return "FATAL";
	}

	return "UNKNOWN";
}

const char* Log::LevelToColor(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Trace: return "\033[37m";
	case LogLevel::Info:  return "\033[34m";
	case LogLevel::Warn:  return "\033[33m";
	case LogLevel::Error: return "\033[31m";
	case LogLevel::Fatal: return "\033[35m";
	}

	return "\033[0m";
}
}