#pragma once
#include <cassert>
#include "Log.h"

#ifdef DEBUG

    // =========================================================
    // Platform debug break
    // =========================================================

    #ifdef _MSC_VER
        #define GE2D_DEBUGBREAK() __debugbreak()
    #else
        #include <signal.h>
        #define GE2D_DEBUGBREAK() raise(SIGTRAP)
    #endif

    // =========================================================
    // Internal assert helper
    // =========================================================

    #define GE2D_INTERNAL_ASSERT_IMPL(type, check, msg) \
        do \
        { \
            if (!(check)) \
            { \
                type##_FATAL( \
                    "ASSERT FAILED!\n" \
                    << "Message: " << msg << "\n" \
                    << "File: " << __FILE__ << "\n" \
                    << "Line: " << __LINE__ \
                ); \
                GE2D_DEBUGBREAK(); \
            } \
        } while (0)

    // =========================================================
    // Engine asserts
    // =========================================================

    #define GE2D_ASSERT(check, msg) \
        GE2D_INTERNAL_ASSERT_IMPL(GE2D, check, msg)

    // =========================================================
    // Client asserts
    // =========================================================

    #define APP_ASSERT(check, msg) \
        GE2D_INTERNAL_ASSERT_IMPL(APP, check, msg)

#else

    // =========================================================
    // Completely stripped in RELEASE
    // =========================================================

    #define GE2D_ASSERT(check, msg)
    #define APP_ASSERT(check, msg)

#endif