
#pragma once

#ifndef SPDLOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ygg {

    class Log {
    public:
        static void Init();
        static void Destroy();
        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static inline bool s_Init = false;
    };
}

#ifdef YGG_LOG

#define YGG_TRACE(...)       ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::trace, __VA_ARGS__)
#define YGG_INFO(...)        ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::info, __VA_ARGS__)
#define YGG_WARNING(...)     ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::warn, __VA_ARGS__)
#define YGG_WARN(...)     ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::warn, __VA_ARGS__)
#define YGG_ERROR(...)       ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::err, __VA_ARGS__)
#define YGG_CRITICAL(...)    ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::critical, __VA_ARGS__)

#else

#define YGG_TRACE(...)
#define YGG_INFO(...)
#define YGG_WARNING(...)
#define YGG_WARN(...)
#define YGG_ERROR(...)
#define YGG_CRITICAL(...)

#endif