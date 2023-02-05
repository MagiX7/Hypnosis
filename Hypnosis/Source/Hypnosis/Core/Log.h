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

#ifdef HS_DEBUG

	#define HS_CORE_INFO(...)  ::Hypnosis::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define HS_CORE_WARN(...)  ::Hypnosis::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define HS_CORE_TRACE(...) ::Hypnosis::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define HS_CORE_ERROR(...) ::Hypnosis::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define HS_CORE_FATAL(...) ::Hypnosis::Log::GetCoreLogger()->fatal(__VA_ARGS__)
	
	#define HS_INFO(...)  ::Hypnosis::Log::GetClientLogger()->info(__VA_ARGS__)
	#define HS_WARN(...)  ::Hypnosis::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define HS_TRACE(...) ::Hypnosis::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define HS_ERROR(...) ::Hypnosis::Log::GetClientLogger()->error(__VA_ARGS__)
	#define HS_FATAL(...) ::Hypnosis::Log::GetClientLogger()->fatal(__VA_ARGS__)

#else

	#define HS_CORE_INFO(...)
	#define HS_CORE_WARN(...)
	#define HS_CORE_TRACE(...)
	#define HS_CORE_ERROR(...)
	#define HS_CORE_FATAL(...)
	
	#define HS_INFO(...)
	#define HS_WARN(...)
	#define HS_TRACE(...)
	#define HS_ERROR(...)
	#define HS_FATAL(...)

#endif