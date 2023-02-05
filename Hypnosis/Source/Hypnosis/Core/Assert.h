#pragma once

#include "Hypnosis/Core/Core.h"
#include "Hypnosis/Core/Log.h"
#include <filesystem>

#ifdef HS_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define HS_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { HS##type##ERROR(msg, __VA_ARGS__); HS_DEBUGBREAK(); } }
#define HS_INTERNAL_ASSERT_WITH_MSG(type, check, ...) HS_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define HS_INTERNAL_ASSERT_NO_MSG(type, check) HS_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", HS_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define HS_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define HS_INTERNAL_ASSERT_GET_MACRO(...) HS_EXPAND_MACRO( HS_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, HS_INTERNAL_ASSERT_WITH_MSG, HS_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define HS_ASSERT(...) HS_EXPAND_MACRO( HS_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define HS_CORE_ASSERT(...) HS_EXPAND_MACRO( HS_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define HS_ASSERT(...)
#define HS_CORE_ASSERT(...)
#endif