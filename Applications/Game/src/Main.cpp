
#include "IApplication.h"
#include "Log.h"
#include "Runtime.h"
#include "RuntimeConfig.h"

namespace
{

//===========================================================
class GameApp : public GE2D::IApplication
{
public:
	void OnInit() override
	{
		APP_INFO("Game initialized");
	}
};

} // namespace


//===========================================================
int main()
{
	GE2D::RuntimeConfig config;
	config.t_AppName = "Game";
	config.t_Width = 1280;
	config.t_Height = 720;
	config.t_Mode = GE2D::RuntimeMode::Client;
	config.t_Headless = false;
	config.t_TargetFrameRate = 120;

	GE2D::Runtime runtime(config);
	GameApp app;

	APP_INFO("Starting app: " << config.t_AppName);
	return runtime.Run(app);
}
