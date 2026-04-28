project "Core"
    location "Engine/Core"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir)
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

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "On"

    filter {}