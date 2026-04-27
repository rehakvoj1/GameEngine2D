workspace "Engine"
    architecture "x64"
    startproject "Sandbox"

    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SDL"] = "vendor/SDL/include"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["imgui"] = "vendor/imgui"

group "Dependencies"
    include "vendor/premake/SDL.lua"
    include "vendor/premake/imgui.lua"
group ""

include "Engine/Core"
include "Engine/Render"
include "Sandbox"