workspace "Breakout"
	configurations { "Debug", "Release" }
    platforms { "x64" }

project "Breakout"
	kind "ConsoleApp"
	language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs { "src" }

    filter { "platforms:x64" }
    system "Windows"
    architecture "x86_64"

    files { "**.h", "**.cpp" }

    filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

    filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"