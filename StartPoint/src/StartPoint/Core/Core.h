#pragma once
#include <memory>

// Use predefined macros to detect current platform.
#ifdef _WIN32
	#ifdef _WIN64
		#define SP_PLATFORM_WINDOWS
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	// MacOS's platfrom define.
#elif defined(__ANDROID)
	// Android's platfrom define.
#elif defined(__linux__)
	// Linux's platfrom define.
#else
	#error "Unknown Platform!"
#endif

// Debug mode debugbreak macros define.
#ifdef SP_DEBUG
	#if defined(SP_PLATFORM_WINDOWS)
		#define SP_DEBUGBREAK() __debugbreak()
	#elif defined(SP_PLATFORM_LINUX)
		// Linux system debugbreak macros define.
	#else
		#error "Your Platform is not supported debugbreak!"
	#endif
	#define SP_ENABLE_ASSERT
#else
	#define SP_DEBUGBREAK()
#endif

// If debug mode, enable assert macros.
#ifdef SP_ENABLE_ASSERT
	#define SP_ASSERT(x,...) {if(!(x)) {SP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define SP_CORE_ASSERT(x, ...) {if(!(x)) {SP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define SP_ASSERT(x,...)
	#define SP_CORE_ASSERT(x, ...)
#endif

// ::TODO
#ifdef SP_PLATFORM_WINDOWS
	#if SP_DYNAMIC_LINK
		#ifdef SP_BUILD_DLL
			#define SP_API __declspec(dllexport)
		#else
			#define SP_API __declspec(dllimport)
		#endif
	#else
		#define SP_API
	#endif
#else
	#error StartPoint Only Suppert Windows
#endif

#define BIT(x) (1 << x)

#define SP_BIND_ENENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define GLFW_INCLUDE_NONE

namespace StartPoint 
{

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