#pragma once

#include <cstdint>
#include <string>

namespace GE2D {

//========================================
enum class RuntimeMode
{
	Client,
	DedicatedServer,
	Editor
};

//========================================
struct RuntimeConfig
{
	std::string t_AppName;
	std::uint32_t t_Width{ 0 };
	std::uint32_t t_Height{ 0 };

	RuntimeMode t_Mode{ RuntimeMode::Client };
	bool t_Headless{ false };

	double t_FixedTimeStep{ 1.0 / 60.0 };
	double t_MaxFrameDelta{ 0.25 };
	std::uint32_t t_MaxFixedStepsPerFrame{ 5 };

	// Zero means unrestricted. Headless/server builds should usually leave this at zero
	// and sleep from fixed tick timing instead of rendering cadence.
	std::uint32_t t_TargetFrameRate{ 0 };
};

} // GE2D namespace
