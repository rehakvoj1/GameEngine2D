#include <algorithm>
#include <thread>

#include "Runtime.h"
#include "Log.h"

namespace GE2D {
	



//===========================================================
const char* RuntimeModeToString(RuntimeMode mode)
{
	switch (mode)
	{
	case RuntimeMode::Client: return "Client";
	case RuntimeMode::DedicatedServer: return "DedicatedServer";
	case RuntimeMode::Editor: return "Editor";
	}

	return "Unknown";
}


//===========================================================
Runtime::Runtime(const RuntimeConfig& config) :
	m_config{config}
{

}


//===========================================================
bool Runtime::Initialize()
{
	Log::Init();

	if (m_config.t_FixedTimeStep <= 0.0)
	{
		GE2D_ERROR("Runtime fixed timestep must be greater than zero");
		return false;
	}

	if (m_config.t_MaxFrameDelta <= 0.0)
	{
		GE2D_ERROR("Runtime max frame delta must be greater than zero");
		return false;
	}

	GE2D_INFO("Initializing runtime: " << m_config.t_AppName);
	GE2D_INFO("Runtime mode: " << RuntimeModeToString(m_config.t_Mode)
		<< ", headless: " << (m_config.t_Headless ? "true" : "false"));

	m_Running = true;
	return true;
}


//===========================================================
int Runtime::Run(IApplication& app)
{
	using Clock = std::chrono::steady_clock;
	using TimePoint = Clock::time_point;

	if (!Initialize())
	{
		return 1;
	}

	app.OnInit();

	double accumulator = 0.0;
	TimePoint previous = Clock::now();

	GE2D_INFO("Runtime running...");
	while (m_Running && !app.ShouldQuit())
	{
		TimePoint frameStart = Clock::now();
		TimePoint current = Clock::now();
		std::chrono::duration<double> delta = current - previous;
		double deltaTime = delta.count();
		previous = current;

		deltaTime = std::min(deltaTime, m_config.t_MaxFrameDelta);
		accumulator += deltaTime;

		FrameContext frameContext;
		frameContext.DeltaTime = deltaTime;
		frameContext.FrameIndex = m_FrameIndex;

		app.OnPreFrame(frameContext);

		if (!m_config.t_Headless)
		{
			app.OnPlatformEvents(frameContext);
			app.OnInput(frameContext);
		}

		app.OnNetworkReceive(frameContext);
		app.OnPreSimulation(frameContext);

		std::uint32_t fixedSteps = 0;
		while (accumulator >= m_config.t_FixedTimeStep
			&& fixedSteps < m_config.t_MaxFixedStepsPerFrame)
		{
			SimulationContext simulationContext;
			simulationContext.FixedDeltaTime = m_config.t_FixedTimeStep;
			simulationContext.TickIndex = m_TickIndex;

			app.OnFixedUpdate(simulationContext);

			accumulator -= m_config.t_FixedTimeStep;
			++m_TickIndex;
			++fixedSteps;
		}

		if (accumulator >= m_config.t_FixedTimeStep)
		{
			GE2D_WARN("Dropping accumulated simulation time after "
				<< m_config.t_MaxFixedStepsPerFrame << " fixed steps");
			accumulator = std::min(accumulator, m_config.t_FixedTimeStep);
		}

		frameContext.InterpolationAlpha = accumulator / m_config.t_FixedTimeStep;

		app.OnPostSimulation(frameContext);

		if (!m_config.t_Headless)
		{
			app.OnAnimation(frameContext);
			app.OnAudio(frameContext);
			app.OnRenderPreparation(frameContext);
			app.OnRender(frameContext);
		}

		app.OnNetworkSend(frameContext);
		app.OnEndFrame(frameContext);

		++m_FrameIndex;
		SleepForFrameLimit(frameStart);
	}

	app.OnShutdown();
	Shutdown();

	return 0;
}


//===========================================================
void Runtime::RequestStop()
{
	m_Running = false;
}


//===========================================================
void Runtime::SleepForFrameLimit(const std::chrono::steady_clock::time_point& frameStart) const
{
	if (m_config.t_TargetFrameRate == 0)
	{
		if (m_config.t_Headless)
		{
			std::this_thread::sleep_for(std::chrono::duration<double>(m_config.t_FixedTimeStep));
		}

		return;
	}

	const double targetFrameSeconds = 1.0 / static_cast<double>(m_config.t_TargetFrameRate);
	const auto targetDuration = std::chrono::duration<double>(targetFrameSeconds);
	const auto elapsed = std::chrono::steady_clock::now() - frameStart;

	if (elapsed < targetDuration)
	{
		std::this_thread::sleep_for(targetDuration - elapsed);
	}
}


//===========================================================
void Runtime::Shutdown()
{
	GE2D_INFO("Shutting down...");
	m_Running = false;
}


} // GE2D namespace
