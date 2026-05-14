#include "RuntimeConfig.h"
#include "Runtime.h"
#include "Sandbox.h"
#include "Log.h"

//===========================================================
int main()
{
	GE2D::RuntimeConfig config;
	config.t_AppName = "Sandbox";
	config.t_Width = 1280;
	config.t_Height = 720;
	config.t_Mode = GE2D::RuntimeMode::Client;
	config.t_Headless = false;
	config.t_TargetFrameRate = 120;

	GE2D::Runtime runtime(config);
	SandboxApp app;

	APP_INFO("Starting app: " << config.t_AppName);
	return runtime.Run(app);
}
