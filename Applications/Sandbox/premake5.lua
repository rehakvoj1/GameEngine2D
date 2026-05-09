project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{ROOT_DIR}build/bin/" .. outputdir)
    objdir ("%{ROOT_DIR}build/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{ROOT_DIR}Applications/Sandbox/src/**.h",
        "%{ROOT_DIR}Applications/Sandbox/src/**.cpp"
    }

    includedirs {
        "%{ROOT_DIR}Engine/Core/src",
        "%{ROOT_DIR}Engine/Render/src"
    }

    links {
        "Core",
        "Render"
    }

    dependson { "Core", "Render" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter {}
