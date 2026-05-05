project "SDL3"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    targetdir ("%{ROOT_DIR}build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{ROOT_DIR}build/bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "%{ROOT_DIR}vendor/SDL/include/build_config",
        "%{ROOT_DIR}vendor/SDL/include",
        "%{ROOT_DIR}vendor/SDL/src"
    }

    -- pouze common (platform-independent) kód
    files {
        "%{ROOT_DIR}vendor/SDL/src/*.c",
        "%{ROOT_DIR}vendor/SDL/src/atomic/*.c",
        "%{ROOT_DIR}vendor/SDL/src/audio/*.c",
        "%{ROOT_DIR}vendor/SDL/src/cpuinfo/*.c",
        "%{ROOT_DIR}vendor/SDL/src/dynapi/*.c",
        "%{ROOT_DIR}vendor/SDL/src/events/*.c",
        "%{ROOT_DIR}vendor/SDL/src/file/*.c",
        "%{ROOT_DIR}vendor/SDL/src/haptic/*.c",
        "%{ROOT_DIR}vendor/SDL/src/joystick/*.c",
        "%{ROOT_DIR}vendor/SDL/src/libm/*.c",
        "%{ROOT_DIR}vendor/SDL/src/locale/*.c",
        "%{ROOT_DIR}vendor/SDL/src/misc/*.c",
        "%{ROOT_DIR}vendor/SDL/src/power/*.c",
        "%{ROOT_DIR}vendor/SDL/src/render/*.c",
        "%{ROOT_DIR}vendor/SDL/src/stdlib/*.c",
        "%{ROOT_DIR}vendor/SDL/src/thread/*.c",
        "%{ROOT_DIR}vendor/SDL/src/timer/*.c",
        "%{ROOT_DIR}vendor/SDL/src/video/*.c",
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "_WINDOWS",
            "SDL_BUILDING_LIBRARY",
            "SDL_PLATFORM_WINDOWS",
            "SDL_VIDEO_DRIVER_WINDOWS",
            "SDL_AUDIO_DRIVER_WASAPI",
            "SDL_AUDIO_DRIVER_DSOUND"
        }

        -- Windows-specific implementace
        files {
            "%{ROOT_DIR}vendor/SDL/src/core/windows/*.c",
            "%{ROOT_DIR}vendor/SDL/src/video/windows/*.c",
            "%{ROOT_DIR}vendor/SDL/src/audio/wasapi/*.c",
            "%{ROOT_DIR}vendor/SDL/src/audio/directsound/*.c",
            "%{ROOT_DIR}vendor/SDL/src/joystick/windows/*.c",
            "%{ROOT_DIR}vendor/SDL/src/haptic/windows/*.c",
            "%{ROOT_DIR}vendor/SDL/src/thread/windows/*.c",
            "%{ROOT_DIR}vendor/SDL/src/timer/windows/*.c",
            "%{ROOT_DIR}vendor/SDL/src/loadso/windows/*.c",
            "%{ROOT_DIR}vendor/SDL/src/filesystem/windows/*.c",
            "%{ROOT_DIR}vendor/SDL/src/power/windows/*.c",
            "%{ROOT_DIR}vendor/SDL/src/misc/windows/*.c",
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