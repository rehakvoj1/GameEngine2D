project "Core"
    location "Engine/Core"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "Core.h"
    pchsource "Engine/Core/src/Core.cpp"

    files {
        "Engine/Core/src/**.h",
        "Engine/Core/src/**.cpp"
    }

    includedirs {
        "%{IncludeDir.SDL}",
        "%{IncludeDir.glm}"
    }

    links {
        "SDL3"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "CORE_BUILD_DLL", "PLATFORM_WINDOWS" }