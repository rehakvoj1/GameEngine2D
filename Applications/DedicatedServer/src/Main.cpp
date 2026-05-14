#include "IApplication.h"
#include "Log.h"
#include "Runtime.h"
#include "RuntimeConfig.h"

namespace
{

//===========================================================
class DedicatedServerApp : public GE2D::IApplication
{
public:
	void OnInit() override
	{
		APP_INFO("Dedicated server initialized");
	}

	void OnNetworkReceive(const GE2D::FrameContext& context) override
	{
		(void)context;
	}

	void OnFixedUpdate(const GE2D::SimulationContext& context) override
	{
		(void)context;
	}

	void OnNetworkSend(const GE2D::FrameContext& context) override
	{
		(void)context;
	}
};

} // namespace


//===========================================================
int main()
{
	GE2D::RuntimeConfig config;
	config.t_AppName = "DedicatedServer";
	config.t_Mode = GE2D::RuntimeMode::DedicatedServer;
	config.t_Headless = true;
	config.t_FixedTimeStep = 1.0 / 60.0;
	config.t_MaxFixedStepsPerFrame = 8;

	GE2D::Runtime runtime(config);
	DedicatedServerApp app;

	APP_INFO("Starting app: " << config.t_AppName);
	return runtime.Run(app);
}
