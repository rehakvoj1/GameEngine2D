project "DedicatedServer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{ROOT_DIR}build/bin/" .. outputdir)
    objdir ("%{ROOT_DIR}build/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{ROOT_DIR}Applications/DedicatedServer/src/**.h",
        "%{ROOT_DIR}Applications/DedicatedServer/src/**.cpp"
    }

    includedirs {
        "%{ROOT_DIR}Engine/Core/src"
    }

    links {
        "Core"
    }

    dependson { "Core" }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "On"

    filter {}
