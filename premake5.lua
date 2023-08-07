workspace "StartPoint"          -- workspace -> Solution
    architecture "x64"          -- architecture -> CPU architecture
    
    configurations              -- configurations -> Build configurations, the default provided by most IDEs is "Debug" and "Release"
    {
        "Debug",
        -- "Release",
    }

-- outputdir -> Golbal variable.
-- %{} -> Value tokens.
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "StartPoint"            -- porject -> Project in solution.
    location "StartPoint"       -- location -> The location of current project
    kind "StaticLib"            -- kind -> Kind of current project.
    language "C++"              -- language -> Selected language. 

    -- targetdir -> The output files direction.
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    -- objdir -> The obj files direction.
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 

    -- files -> Files that need to be compiled.
    files                      
    {
        -- %{prj.name} is current project's name. For example, current project's name is StartPoint.
        -- **.h means all the files with a file suffix of h.
        -- **.cpp is the same.
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    
    -- include -> The include headfiles path.
    includedirs         
    {
        "%{prj.name}/src",
        "%{prj.name}/vender/Include",
        "%{prj.name}/vender/imgui"
    }


    filter "system:windows"     -- filter -> Can filter by specific build configurations or platforms, operating system, target actions for the exact configurations.
        cppdialect "C++17"
        staticruntime "On"      -- staticruntime -> Default(no set),On(MultiThreaded),Off(MultiThreadedDLL).
        systemversion "latest"  -- systemversion -> Use the latest version of the SDK available or specify the version of the SDK you want(Such as 10.0.10240.0).
        
        -- defines -> Preprocessing macro definition.
        defines                
        {
            "SP_PLATFORM_WINDOWS",
            "SP_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "IMGUI_API=__declspec(dllexport)"
        }

        postbuildcommands       -- postbuildcommands -> Specifies shell commands to run after build is finished.
        {

        }

    filter "configurations:Debug"
        defines "SP_DEBUG"
        symbols "On"            -- symbols -> Turn on/off debug symbol table generation.

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"            
    language "C++"              
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs   
    {
        "%{wks.location}/StartPoint/src",
        "%{wks.location}/StartPoint/vender/Include",
        "%{wks.location}/StartPoint/vender/imgui"
    }

    libdirs                     -- libdirs -> Specifies the library search paths for the linker.
    { 
        "StartPoint/vender/Libs"
    }

    links                       -- links -> Specifies a list of libraries and projects to link against.
    {
        "StartPoint",
        "opengl32.lib",
        "glfw3.lib",
        "spdlogd.lib",
        "GLAD.lib",
        "ImGui.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
        defines
        {
            "GLFW_INCLUDE_NONE"
        }
    
    filter "configurations:Debug"
        defines "SP_DEBUG"
        symbols "On"            -- symbols -> Turn on/off debug symbol table generation.

project "Editor"
    location "Editor"
    kind "ConsoleApp"          
    language "C++"              
        
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs   
    {
        "/StartPoint/src",
        "../StartPoint/vender/Include",
        "../StartPoint/vender/imgui"
    }
    
    libdirs                     -- libdirs -> Specifies the library search paths for the linker.
    { 
        "StartPoint/vender/Libs"
    }
    
    links                       -- links -> Specifies a list of libraries and projects to link against.
    {
        "StartPoint",
        "opengl32.lib",
        "glfw3.lib",
        "spdlogd.lib",
        "GLAD.lib",
        "ImGui.lib",
        "user32.lib",
        "gdi32.lib",
        "shell32.lib"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
    filter "configurations:Debug"
        defines "SP_DEBUG"
        symbols "On"            -- symbols -> Turn on/off debug symbol table generation.
    
   