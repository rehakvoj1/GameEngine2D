
#include "IApplication.h"
#include "Log.h"
#include "Runtime.h"
#include "RuntimeConfig.h"

namespace
{

//===========================================================
class EditorApp : public GE2D::IApplication
{
public:
	void OnInit() override
	{
		APP_INFO("Editor initialized");
	}
};

} // namespace


//===========================================================
int main()
{
	GE2D::RuntimeConfig config;
	config.t_AppName = "Editor";
	config.t_Width = 1600;
	config.t_Height = 900;
	config.t_Mode = GE2D::RuntimeMode::Editor;
	config.t_Headless = false;
	config.t_TargetFrameRate = 120;

	GE2D::Runtime runtime(config);
	EditorApp app;

	APP_INFO("Starting app: " << config.t_AppName);
	return runtime.Run(app);
}
