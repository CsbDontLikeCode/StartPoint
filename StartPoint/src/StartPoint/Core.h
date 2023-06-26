#pragma once

#ifdef SP_PLATFORM_WINDOWS
	#ifdef SP_BUILD_DLL
		#define SP_API __declspec(dllexport)
	#else
		#define SP_API __declspec(dllimport)
	#endif
#else
	#error StartPoint Only Suppert Windows
#endif

#ifdef SP_ENABLE_ASSERT
	#define SP_ASSERT(x,...) {if(!(x)) {SP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define SP_CORE_ASSERT(x, ...) {if(!(x)) {SP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define SP_ASSERT(x,...)
	#define SP_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)