project "Core"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{ROOT_DIR}build/bin/" .. outputdir)
    objdir ("%{ROOT_DIR}build/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{ROOT_DIR}Engine/Core/src/**.h",
        "%{ROOT_DIR}Engine/Core/src/**.cpp"
    }
    
    vpaths {
        ["Header Files"] = { "**.h" },
        ["Source Files"] = { "**.cpp" },
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