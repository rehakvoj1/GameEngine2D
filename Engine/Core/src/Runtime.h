#pragma once
#include <chrono>

#include "Core.h"
#include "IApplication.h"
#include "RuntimeConfig.h"


namespace GE2D {


//===========================================================
class CORE_API Runtime
{
public:
	explicit Runtime(const RuntimeConfig& config);

	bool Initialize();
	int Run(IApplication& app);
	void RequestStop();
	void Shutdown();

private:
	void SleepForFrameLimit(const std::chrono::steady_clock::time_point& frameStart) const;

	bool m_Running{ false };
	const RuntimeConfig& m_config;
	std::uint64_t m_FrameIndex{ 0 };
	std::uint64_t m_TickIndex{ 0 };
};


} // GE2D namespace
