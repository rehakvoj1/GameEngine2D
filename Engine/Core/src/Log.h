#pragma once
#include <sstream>

#include "Core.h"

namespace GE2D
{


// =========================================================
enum class LogLevel
{
	Trace,
	Info,
	Warn,
	Error,
	Fatal
};


// =========================================================
class CORE_API Log
{
public:
	static void Init();

	static void Print(LogLevel level, const std::string& tag, const std::string& message);

private:
	static const char* LevelToString(LogLevel level);
	static const char* LevelToColor(LogLevel level);
};


} // GE2D namespace

// =========================================================
// Internal helper
// =========================================================
#ifdef DEBUG
	#define GE2D_LOG(level, tag, ...) \
		do \
		{ \
			std::stringstream ss; \
			ss << __VA_ARGS__; \
			GE2D::Log::Print(level, tag, ss.str()); \
		} while (0)
	

	// =========================================================
	// Engine logs
	// =========================================================
	#define GE2D_TRACE(msg) GE2D_LOG(GE2D::LogLevel::Trace, "ENGINE", msg)
	#define GE2D_INFO(msg)  GE2D_LOG(GE2D::LogLevel::Info,  "ENGINE", msg)
	#define GE2D_WARN(msg)  GE2D_LOG(GE2D::LogLevel::Warn,  "ENGINE", msg)
	#define GE2D_ERROR(msg) GE2D_LOG(GE2D::LogLevel::Error, "ENGINE", msg)
	#define GE2D_FATAL(msg) GE2D_LOG(GE2D::LogLevel::Fatal, "ENGINE", msg)
	
	// =========================================================
	// Client logs
	// =========================================================
	#define APP_TRACE(msg) GE2D_LOG(GE2D::LogLevel::Trace, "APP", msg)
	#define APP_INFO(msg)  GE2D_LOG(GE2D::LogLevel::Info,  "APP", msg)
	#define APP_WARN(msg)  GE2D_LOG(GE2D::LogLevel::Warn,  "APP", msg)
	#define APP_ERROR(msg) GE2D_LOG(GE2D::LogLevel::Error, "APP", msg)
	#define APP_FATAL(msg) GE2D_LOG(GE2D::LogLevel::Fatal, "APP", msg)
#else
	#define GE2D_TRACE(msg)
	#define GE2D_INFO(msg) 
	#define GE2D_WARN(msg) 
	#define GE2D_ERROR(msg)
	#define GE2D_FATAL(msg)
	
	#define APP_TRACE(msg)
	#define APP_INFO(msg) 
	#define APP_WARN(msg) 
	#define APP_ERROR(msg)
	#define APP_FATAL(msg)
#endif