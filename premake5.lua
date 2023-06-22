workspace "StartPoint"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "StartPoint"
	location "StartPoint"
	kind "SharedLib"
	language "C++"

	targetdir ("bin" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int" .. outputdir .. "/%{prj.name}")

	files
	{
		"{prj.name}/src/**.h",
		"{prj.name}/src/**.cpp"
	}

	include
	{
		"{prj.name}/vender/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22621.0"
		
		defines{
			"SP_PLATFORM_WINDOWS",
			"SP_BUILD_DLL"
		}

		postbuildcommands
		{
			("COPY  %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}