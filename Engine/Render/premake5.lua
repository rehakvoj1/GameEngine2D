project "Render"
    location "Engine/Render"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    ----------------------------------------
    -- SOURCE FILES
    ----------------------------------------
    files {
        "Engine/Render/src/**.h",
        "Engine/Render/src/**.cpp",

        -- ImGui backends (platform + renderer)
        "vendor/imgui/backends/imgui_impl_sdl3.cpp",
        "vendor/imgui/backends/imgui_impl_dx12.cpp"
        -- Vulkan backend se přidá podmíněně níže
    }

    ----------------------------------------
    -- INCLUDE DIRECTORIES
    ----------------------------------------
    includedirs {
        "Engine/Core/src",
        "%{IncludeDir.glm}",
        "%{IncludeDir.imgui}",
        "vendor/imgui/backends"
    }

    ----------------------------------------
    -- LINKS
    ----------------------------------------
    links {
        "Core",
        "SDL3",
        "ImGui"
    }

    ----------------------------------------
    -- PLATFORM: WINDOWS
    ----------------------------------------
    filter "system:windows"
        systemversion "latest"
        defines { "RENDER_BUILD_DLL", "PLATFORM_WINDOWS" }

        -- DirectX 12 (Windows SDK)
        links {
            "d3d12",
            "dxgi",
            "dxguid"
        }

        ----------------------------------------
        -- Vulkan (optional)
        ----------------------------------------
        local vulkan_sdk = os.getenv("VULKAN_SDK")

        if vulkan_sdk ~= nil and vulkan_sdk ~= "" then
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

            -- přidání ImGui Vulkan backendu
            files {
                "vendor/imgui/backends/imgui_impl_vulkan.cpp"
            }
        else
            print("WARNING: VULKAN_SDK not set. Vulkan backend will be disabled.")
        end

    ----------------------------------------
    -- CONFIGURATIONS
    ----------------------------------------
    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "On"

    filter {}