#include <chrono>
#include <iostream>

#include "Runtime.h"
#include "Log.h"

namespace GE2D 
{


	

//===========================================================
Runtime::Runtime(RuntimeConfig& config) :
	m_config{config}
{

}

//===========================================================
bool Runtime::Initialize()
{
	GE2D_INFO("Initializing...");
	Log::Init();
	m_Running = true;
	return true;
}

//===========================================================
int Runtime::Run(IApplication& app)
{
	using Clock = std::chrono::system_clock;
	using TimePoint = Clock::time_point;

	Initialize();

	app.OnInit();

	constexpr float fixedDelta = 1.0f / 60.0f;
	constexpr float maxFrameDelta = 0.25f;

	float accumulator = 0.0f;
	TimePoint previous = Clock::now();

	GE2D_INFO("Runtime running...");
	while (m_Running)
	{
		TimePoint current = Clock::now();
		std::chrono::duration<float> delta = current - previous;
		float deltaTime = delta.count();
		previous = current;

		

		deltaTime = std::min(deltaTime, maxFrameDelta);
		accumulator += deltaTime;

		app.OnUpdate(deltaTime);

		while (accumulator >= fixedDelta)
		{
			app.OnFixedUpdate(fixedDelta);
			accumulator -= fixedDelta;
		}

		

	}

	app.OnShutdown();
	Shutdown();

	return 0;
}

//===========================================================
void Runtime::Shutdown()
{

}

}
