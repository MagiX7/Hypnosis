#pragma once

#include <memory>

#ifdef HS_DEBUG
	#define HS_DEBUGBREAK() __debugbreak()
	#define HS_ENABLE_ASSERTS
#else
	#define HS_DEBUGBREAK()
#endif

//#ifdef HS_ENABLE_ASSERTS
//#define HS_ASSERT(x, ...) { if(!(x)) { HS_ERROR("Assertion Failed: {0}", __VA_ARGS__); HS_DEBUGBREAK(); } }
//#define HS_CORE_ASSERT(x, ...) { if(!(x)) {HS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HS_DEBUGBREAK(); } }
//#endif


#define HS_EXPAND_MACRO(x) x
#define HS_STRINGIFY_MACRO(x) #x

#define BIT(x) 1 << x
#define HS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace Hypnosis {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Hypnosis/Core/Log.h"
#include "Hypnosis/Core/Assert.h"