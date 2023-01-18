#pragma once

#include "Hypnosis/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>

namespace Hypnosis {

	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return clientLogger; }

	private:
		static Ref<spdlog::logger> coreLogger;
		static Ref<spdlog::logger> clientLogger;

	};
}

#ifdef _DEBUG

	#define ZN_CORE_INFO(...)  ::Hypnosis::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define ZN_CORE_WARN(...)  ::Hypnosis::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define ZN_CORE_TRACE(...) ::Hypnosis::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define ZN_CORE_ERROR(...) ::Hypnosis::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define ZN_CORE_FATAL(...) ::Hypnosis::Log::GetCoreLogger()->fatal(__VA_ARGS__)
	
	#define ZN_INFO(...)  ::Hypnosis::Log::GetClientLogger()->info(__VA_ARGS__)
	#define ZN_WARN(...)  ::Hypnosis::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define ZN_TRACE(...) ::Hypnosis::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define ZN_ERROR(...) ::Hypnosis::Log::GetClientLogger()->error(__VA_ARGS__)
	#define ZN_FATAL(...) ::Hypnosis::Log::GetClientLogger()->fatal(__VA_ARGS__)

#else
	#define ZN_CORE_INFO(...)
	#define ZN_CORE_WARN(...)
	#define ZN_CORE_TRACE(...)
	#define ZN_CORE_ERROR(...)
	#define ZN_CORE_FATAL(...)
	
	#define ZN_INFO(...)
	#define ZN_WARN(...)
	#define ZN_TRACE(...)
	#define ZN_ERROR(...)
	#define ZN_FATAL(...)

#endif