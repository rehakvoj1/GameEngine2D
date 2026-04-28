project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "Sandbox/src/**.cpp"
    }

    includedirs {
        "Engine/Core/src",
        "Engine/Render/src"
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