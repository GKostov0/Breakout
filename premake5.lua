workspace "Breakout"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	configurations { "Debug", "Release" }
    platforms { "x64" }

    IncludeDir = {}
    IncludeDir["GLFW"] = "GLFW/include"
    IncludeDir["Glad"] = "Glad/include"

    include "GLFW"
    include "Glad"

project "Breakout"
    location "Breakout"
    kind "ConsoleApp"
	language "C++"
        
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    links 
    {
        "GLFW",
        "Glad",
        "opengl32.lib"
    }

	
    targetdir "bin/%{cfg.buildcfg}"

    includedirs 
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
    }

    filter { "platforms:x64" }
    system "Windows"
    architecture "x86_64"

    files
	{
		"**.h",
		"**.cpp"
	}

    filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

    filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"