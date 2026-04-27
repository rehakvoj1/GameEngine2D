project "SDL3"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "vendor/SDL/src/**.c",
        "vendor/SDL/include/**.h"
    }

    includedirs {
        "vendor/SDL/include"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "_WINDOWS",
            "SDL_BUILDING_LIBRARY"
        }

        files {
            "vendor/SDL/src/core/windows/**.c"
        }

        links {
            "user32",
            "gdi32",
            "winmm",
            "imm32",
            "ole32",
            "oleaut32",
            "version",
            "uuid"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    filter {}