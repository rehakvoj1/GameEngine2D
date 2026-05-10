#include "RuntimeConfig.h"
#include "Runtime.h"
#include "Sandbox.h"


int main()
{
	GE2D::RuntimeConfig config;
	config.t_AppName = "Sandbox";
	config.t_Width = 1280;
	config.t_Height = 720;

	GE2D::Runtime runtime(config);
	SandboxApp app;

	return runtime.Run(app);
}
