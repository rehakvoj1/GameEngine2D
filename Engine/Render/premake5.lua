project "Render"
    location "Engine/Render"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "Engine/Render/src/**.h",
        "Engine/Render/src/**.cpp"
    }

    includedirs {
        "Engine/Core/src",
        "%{IncludeDir.glm}"
    }

    links {
        "Core"
    }

    ----------------------------------------
    -- PLATFORM: WINDOWS
    ----------------------------------------
    filter "system:windows"
        systemversion "latest"
        defines { "RENDER_BUILD_DLL", "PLATFORM_WINDOWS" }

        -- DirectX 12 (součást Windows SDK)
        links {
            "d3d12",
            "dxgi",
            "dxguid"
        }

        ----------------------------------------
        -- Vulkan (podmíněně)
        ----------------------------------------
        local vulkan_sdk = os.getenv("VULKAN_SDK")

        if vulkan_sdk then
            print("Vulkan SDK found at: " .. vulkan_sdk)

            includedirs {
                vulkan_sdk .. "/Include"
            }

            libdirs {
                vulkan_sdk .. "/Lib"
            }

            links {
                "vulkan-1"
            }

            defines { "RENDER_HAS_VULKAN" }
        else
            print("WARNING: VULKAN_SDK not set. Vulkan backend will be disabled.")
        end

    ----------------------------------------
    -- CONFIGURATIONS
    ----------------------------------------
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        optimize "On"

    filter {}