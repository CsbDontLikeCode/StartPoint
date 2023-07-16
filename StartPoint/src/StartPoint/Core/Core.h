#pragma once
#include <memory>

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

#ifdef SP_ENABLE_ASSERT
	#define SP_ASSERT(x,...) {if(!(x)) {SP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define SP_CORE_ASSERT(x, ...) {if(!(x)) {SP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define SP_ASSERT(x,...)
	#define SP_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SP_BIND_ENENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define GLFW_INCLUDE_NONE

namespace StartPoint 
{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	//template<typename T, typename ... Args>
	//constexpr Scope<T> CreateScope(Args&& ... args) 
	//{
	//	return std::make_unique<T>(std::forward<Args>(args)...)
	//}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	//template<typename T, typename ... Args>
	//constexpr Ref<T> CreateRef(Args&& ... args)
	//{
	//	return std::make_shared<T>(std::forward<Args>(args)...)
	//}

}