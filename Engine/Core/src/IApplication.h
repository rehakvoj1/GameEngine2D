#pragma once

namespace GE2D
{


//class RenderContext;

//===========================================================
class IApplication
{
public:
	virtual ~IApplication() = default;

	virtual void OnInit() {}
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnFixedUpdate(float fixedDeltaTime) {}
	//virtual void OnRender(RenderContext& renderContext) {}
	virtual void OnShutdown() {}
};


} // GE2D namespace