#pragma once
//#include "sppch.h"

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/fmt/ostr.h>

namespace StartPoint {

	class SP_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;}
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log mocros
#define SP_CORE_TRACE(...)	::StartPoint::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SP_CORE_INFO(...)	::StartPoint::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SP_CORE_WARN(...)	::StartPoint::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SP_CORE_ERROR(...)	::StartPoint::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SP_CORE_FATAL(...)	::StartPoint::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log mocros
#define SP_TRACE(...)		::StartPoint::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SP_INFO(...)		::StartPoint::Log::GetClientLogger()->info(__VA_ARGS__)
#define SP_WARN(...)		::StartPoint::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SP_ERROR(...)		::StartPoint::Log::GetClientLogger()->error(__VA_ARGS__)
#define SP_FATAL(...)		::StartPoint::Log::GetClientLogger()->fatal(__VA_ARGS__)
