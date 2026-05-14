#pragma once

#include <cstdint>

namespace GE2D {


//===========================================================
enum class FramePhase
{
	PreFrame,
	PlatformEvents,
	Input,
	NetworkReceive,
	PreSimulation,
	FixedSimulation,
	PostSimulation,
	Animation,
	Audio,
	RenderPreparation,
	Render,
	NetworkSend,
	EndFrame
};

//===========================================================
struct FrameContext
{
	double DeltaTime{ 0.0 };
	double InterpolationAlpha{ 0.0 };
	std::uint64_t FrameIndex{ 0 };
};

//===========================================================
struct SimulationContext
{
	double FixedDeltaTime{ 0.0 };
	std::uint64_t TickIndex{ 0 };
};

//===========================================================
class IApplication
{
public:
	virtual ~IApplication() = default;

	virtual void OnInit() {}
	virtual bool ShouldQuit() const { return false; }

	virtual void OnPreFrame(const FrameContext&) {}
	virtual void OnPlatformEvents(const FrameContext&) {}
	virtual void OnInput(const FrameContext&) {}
	virtual void OnNetworkReceive(const FrameContext&) {}
	virtual void OnPreSimulation(const FrameContext&) {}
	virtual void OnFixedUpdate(const SimulationContext&) {}
	virtual void OnUpdate(const FrameContext&) {}
	virtual void OnPostSimulation(const FrameContext&) {}
	virtual void OnAnimation(const FrameContext&) {}
	virtual void OnAudio(const FrameContext&) {}
	virtual void OnRenderPreparation(const FrameContext&) {}
	virtual void OnRender(const FrameContext&) {}
	virtual void OnNetworkSend(const FrameContext&) {}
	virtual void OnEndFrame(const FrameContext&) {}
	virtual void OnShutdown() {}
};


} // GE2D namespace
