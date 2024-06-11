
#pragma once

#ifndef SPDLOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <csignal>

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

#ifndef __FUNCSIG__
#ifdef __PRETTY_FUNCTION__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#else
#define __FUNCSIG__ __FUNCTION__
#endif
#endif

#ifdef YGG_USE_SIMPLE_FUNCTION
#define YGG_FUNC __FUNCTION__
#else
#define YGG_FUNC __FUNCSIG__
#endif

#ifdef YGG_LOG

#define YGG_TRACE(...)       ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::trace, __VA_ARGS__)
#define YGG_INFO(...)        ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::info, __VA_ARGS__)
#define YGG_WARNING(...)     ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::warn, __VA_ARGS__)
#define YGG_WARN(...)     ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::warn, __VA_ARGS__)
#define YGG_ERROR(...)       ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::err, __VA_ARGS__)
#define YGG_CRITICAL(...)    ::Ygg::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, YGG_FUNC}, spdlog::level::critical, __VA_ARGS__)

#if (_MSC_VER && !__INTEL_COMPILER) || (__MINGW32__ || __MINGW64__)

#define YGG_ASSERT(condition, ...) if(!(condition)) { YGG_ERROR(__VA_ARGS__); __debugbreak(); }
#elif _POSIX
#define YGG_ASSERT(condition, ...) if(!(condition)) { YGG_ERROR(__VA_ARGS__); std::raise(SIGTRAP) }
#else
#define YGG_ASSERT(condition, ...) if(!(condition)) { YGG_ERROR(__VA_ARGS__); }
#endif
#else

#define YGG_TRACE(...)
#define YGG_INFO(...)
#define YGG_WARNING(...)
#define YGG_WARN(...)
#define YGG_ERROR(...)
#define YGG_CRITICAL(...)

#define YGG_ASSERT(x,...)

#endif

#define YGG_CHECK(condition, ...)  if(!(condition)) { YGG_WARNING(__VA_ARGS__); }