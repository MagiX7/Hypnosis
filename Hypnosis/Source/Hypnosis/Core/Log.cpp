#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Hypnosis {

    Ref<spdlog::logger> Log::coreLogger;
    Ref<spdlog::logger> Log::clientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        coreLogger = spdlog::stdout_color_mt("Hypnosis");
        coreLogger->set_level(spdlog::level::trace);
        clientLogger = spdlog::stdout_color_mt("Editor");
        coreLogger->set_level(spdlog::level::trace);

    }

}
