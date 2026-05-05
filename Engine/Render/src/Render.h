#pragma once

#ifdef RENDER_BUILD_DLL
    #define RENDER_API __declspec(dllexport)
#else
    #define RENDER_API __declspec(dllimport)
#endif
