workspace "Engine"
    location "build"
    architecture "x64"
    startproject "Sandbox"

    configurations { "Debug", "Release" }

    multiprocessorcompile "On"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
ROOT_DIR = os.getcwd() .. "/"


IncludeDir = {}
IncludeDir["SDL"]   = ROOT_DIR .. "vendor/SDL/include"
IncludeDir["glm"]   = ROOT_DIR .. "vendor/glm"
IncludeDir["imgui"] = ROOT_DIR .. "vendor/imgui"


group "Dependencies"
    include(ROOT_DIR .. "vendor/premake/SDL.lua") 
    include(ROOT_DIR .. "vendor/premake/imgui.lua") 
group ""



include "Engine/Core"
include "Engine/Render"
include "Sandbox"