project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
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