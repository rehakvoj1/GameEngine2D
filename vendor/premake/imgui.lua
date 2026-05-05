project "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{ROOT_DIR}build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{ROOT_DIR}build/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{ROOT_DIR}vendor/imgui/*.cpp",
        "%{ROOT_DIR}vendor/imgui/*.h"
    }

    includedirs {
        "%{ROOT_DIR}vendor/imgui"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    filter {}