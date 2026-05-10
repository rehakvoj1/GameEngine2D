#pragma once
#include "Core.h"
#include "IApplication.h"
#include "RuntimeConfig.h"


namespace GE2D 
{


//===========================================================
class CORE_API Runtime
{
public:
	explicit Runtime(RuntimeConfig& config);

	bool Initialize();
	int Run(IApplication& app);
	void Shutdown();

private:
	bool m_Running{ false };
	RuntimeConfig& m_config;
};

}
